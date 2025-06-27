# %% [markdown]
# # Анализ датасета
# 
# ## Описание датасета
# 
# Датасет представляет собой коллекцию **постов**, каждый из которых содержит текстовый контент и дополнительную метаинформацию: **категорию** и **дату публикации**. Такой формат данных позволяет анализировать не только содержание постов, но и их распределение по времени и тематическим разделам.  
# 
# Текстовые данные требуют предобработки — очистки от стоп-слов, лемматизации и, возможно, анализа тональности. Метаданные (`категория` и `дата`) дают возможность исследовать динамику публикаций и популярность отдельных тематик. Для более глубокого EDA стоит проверить **баланс категорий** (нет ли дисбаланса классов) и **зависимость активности публикаций от времени** (есть ли сезонность или тренды).  
# 
# Если в данных есть другие скрытые особенности (например, пропуски в метаданных или дубликаты постов), их также стоит учесть при анализе.

# %%
!pip install pandas matplotlib seaborn scikit-learn umap-learn spacy nltk sentence-transformers hdbscan
!python -m spacy download ru_core_news_sm

# %%
import re
import math
import warnings
from collections import Counter

import pandas as pd
from scipy.stats import kruskal
from scipy.sparse import hstack
import spacy
import nltk
from nltk.corpus import stopwords

import matplotlib.pyplot as plt
import seaborn as sns

from sklearn.feature_extraction.text import (
    TfidfVectorizer, 
    CountVectorizer
)
from umap.umap_ import UMAP
from sklearn.manifold import TSNE
from sklearn.metrics import classification_report, confusion_matrix
from sklearn.model_selection import train_test_split
from sklearn.metrics import f1_score

import torch
from transformers import AutoTokenizer, AutoModelForSequenceClassification, Trainer, TrainingArguments
import lightgbm as lgb
from sentence_transformers import SentenceTransformer

warnings.simplefilter(action='ignore', category=FutureWarning)

# %% [markdown]
# ### Размер и структура

# %%
df = pd.read_csv('all_channel_posts.csv', parse_dates=['date'])
df.head()

# %%
print(f"Размер датасета: {len(df)} постов")
print(f"Колонки: {df.columns.tolist()}")
df.info()

# %% [markdown]
# Датасет содержит **22 099 постов** и имеет четкую структуру без пропусков — все 6 колонок полностью заполнены. Ключевые поля включают:  
# - `text` (основной контент для NLP-анализа),  
# - `date` (временная метка в формате *datetime64[ns, UTC]* для изучения динамики публикаций),  
# - `category` (категориальная метка для тематической классификации).  
# 
# Технические колонки `message_id` и `sender_id` (тип *int64*) идентифицируют авторов и записи, а `channel` (*object*) указывает источник публикации.  
# 
# Объем данных достаточен для выявления статистически значимых закономерностей, но при работе с текстами может потребоваться уменьшение размерности (например, через TF-IDF или эмбеддинги).
# 
# Типы данных соответствуют ожидаемым: *datetime64[ns, UTC]* для дат, *int64* для идентификаторов и *object* для текстовых/категориальных полей. Такой набор позволяет сразу перейти к анализу без дополнительной очистки пропусков.  
# 
# Для работы с текстами потребуется предобработка: нормализация (стемминг/лемматизация), удаление стоп-слов и, возможно, векторизация (TF-IDF, Word2Vec). Объем данных достаточен для статистически значимых выводов, но при построении ML-моделей может потребоваться балансировка категорий.

# %% [markdown]
# ### Анализ качества данных

# %%
print(f"Пропуски в данных:\n{df.isnull().sum()}")
print(f"\nПолные дубликаты: {df.duplicated().sum()}")
print(f"Дубликаты текста: {df['text'].duplicated().sum()}")
print(f"Дубликаты текста с категориями: {df.duplicated(subset=['text', 'category']).sum()}")

# %% [markdown]
# Датасет демонстрирует хорошую целостность - все столбцы полностью заполнены без пропусков, что сразу позволяет перейти к содержательному анализу. Однако обнаружены текстовые дубликаты: 772 полностью идентичных сообщения и 740 случаев, где совпадает и текст, и категория.
# 
# Эти дубликаты представляют определенную проблему. При сохранении всех копий модели машинного обучения получат перекошенное представление о важности повторяющихся сообщений. Особенно критично это для частотных методов анализа текста, где дубли автоматически получат повышенный вес.
# 
# **Рекомендуемые действия:**
# - Удаление полных дубликатов текста (772 записи) - критично для NLP-анализа
# - Анализ дублей текста с разными категориями (32 случая) - возможно, это ошибки разметки
# - Проверка причин дублирования (автоматическая генерация, кросс-постинг, технические сбои)

# %%
df = df.drop_duplicates(subset=['text'])
df = df[df['category'] != 'other']
df = df.reset_index(drop=True)

# %%
categories = df['category'].unique()
n_categories = len(categories)

cols = 2
rows = math.ceil(n_categories / cols)

# %% [markdown]
# ### Распределение по категориям

# %%
category_percent = df['category'].value_counts(normalize=True).sort_values(ascending=False) * 100

plt.figure(figsize=(12, 6))
sns.barplot(x=category_percent.index, y=category_percent.values, palette='viridis')
plt.title('Процентное распределение по категориям', fontsize=14)
plt.xlabel('Категория')
plt.ylabel('Процент')
plt.xticks(rotation=30)
plt.show()

# %% [markdown]
# Анализ категориального распределения выявил значительный дисбаланс классов. Например, категория "Политика" составляет более 20% всех постов, тогда как "Реклама" не превышает 2.5%. Такой перекос существенно влияет на качество будущих моделей классификации, поскольку алгоритмы будут склонны чаще предсказывать доминирующий класс для опти
# 
# **Решение проблемы:**
# - Использовать стратифицированное разбиение (stratify).
# - Оценивать модель по F1-мере вместо accuracy.
# - Применить взвешивание классов или сэмплирование.

# %% [markdown]
# ### Анализ длины текста

# %%
df['text_length'] = df['text'].apply(lambda x: len(x.split()))
print(f"Средняя длина: {df['text_length'].mean():.1f} слов")
print(f"Медианная длина: {df['text_length'].median()} слов")

plt.figure(figsize=(10, 6))
sns.histplot(df['text_length'], bins=50, kde=True)
plt.title('Распределение длины текста', fontsize=14)
plt.xlabel('Количество слов')
plt.ylabel('Частота')
plt.show()

# %%
fig, axes = plt.subplots(rows, cols, figsize=(14, 5 * rows))
axes = axes.flatten()
palette = sns.color_palette("tab10", len(categories))

for i, (category, color) in enumerate(zip(categories, palette)):
    ax = axes[i]
    sns.histplot(df[df['category'] == category]['text_length'], bins=30, kde=True, color=color, ax=ax)
    ax.set_title(f'Категория: {category}', fontsize=12)
    ax.set_xlabel('Количество слов')
    ax.set_ylabel('Частота')

for j in range(i+1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()
plt.show()

# %% [markdown]
# Исследование длины сообщений выявило значительные различия между категориями. **IT-тематика** лидирует по объёму контента со средним показателем 73.8 слова на пост, что на 45% больше, чем у аутсайдера - категории "Погода" (28.6 слов). Медианные значения демонстрируют аналогичную картину: от 61 слова в IT до 26 слов в сообщениях о погоде.
# 
# Наблюдается чёткая **тематическая закономерность**:
# - Технические и профессиональные категории (**IT**, **Бизнес**) содержат наиболее развёрнутые сообщения
# - Личные и развлекательные темы (**Личное**, **Игры**) занимают средние позиции
# - Утилитарные категории (**Финансы**, **Погода**) отличаются максимальной лаконичностью
# 
# Особого внимания заслуживают:
# 1. **Политика** - при среднем показателе 55.8 слов имеет одну из самых низких медиан (38 слов), что указывает на большое количество крайне коротких сообщений на фоне отдельных длинных постов
# 2. **Реклама** - демонстрирует сбалансированные показатели (59.9/52), что говорит о стандартизированном подходе к созданию коммерческих сообщений
# 
# Разница между средним и медианным значениями (особенно заметная в "Политике") указывает на наличие выбросов - как очень длинных, так и предельно кратких сообщений. Это подтверждает необходимость дополнительного анализа распределения длин внутри каждой категории.

# %% [markdown]
# ### Предобработка данных

# %%
nltk.download('stopwords')

stop = set(stopwords.words('russian'))
nlp = spacy.load('ru_core_news_sm')

def clean_text_symbols(text: str) -> str:
    text = re.sub(r"(https?://|www\.)\S+|bit\.ly/\S+|t\.co/\S+", "", text)  
    text = re.sub(r"#[\wа-яА-ЯёЁ]+", "", text)  
    text = re.sub(r"@[\wа-яА-ЯёЁ]+", "", text)  
    text = re.sub(r"<.*?>", "", text)
    text = re.sub(r"(\*\*|__)(.*?)\1", r"\2", text)
    text = re.sub(r"(\*|_)(.*?)\1", r"\2", text)
    text = re.sub(r"~~(.*?)~~", r"\1", text)
    text = re.sub(r"`{1,2}(.*?)`{1,2}", r"\1", text)
    text = re.sub(r"#{1,6}\s*", "", text)
    text = re.sub(r"\[(.*?)\]\(.*?\)", r"\1", text)
    text = re.sub(r"!\[.*?\]\(.*?\)", "", text)
    text = re.sub(r">\s*", "", text)
    text = re.sub(r"[^a-zA-Zа-яА-ЯёЁ\s]", "", text)
    text = re.sub(r"\s+", " ", text).strip()
    return text

def remove_stop_words(text: str, stop: set) -> str:
    text = " ".join([word for word in text.split() if word not in stop])
    return text

def lemmatize_text(text: str) -> str:
    doc = nlp(text)
    lemmas = [token.lemma_ for token in doc]
    return ' '.join(lemmas) 

def preprocess_text(text: str, stop: set) -> str:
    text = text.lower()
    text = clean_text_symbols(text)
    text = lemmatize_text(text)
    text = remove_stop_words(text, stop)
    return text

df['clean_text'] = df['text'].apply(lambda x: preprocess_text(x, stop))

# %% [markdown]
# Так как в большинстве каналов принято добавлять в конец постов ссылку на свой канал, их стоит удалить тк они не несут смысловой нагрузки.

# %%
def get_last_text_line(text: str) -> str:
    if len(text.split('\n')) == 1:
        return ""
    return text.strip().split('\n')[-1]

def remove_frequent_last_line(text: str, frequent_lines: list) -> str:
    lines = text.strip().split('\n')
    if len(lines) > 1 and lines[-1] in frequent_lines:
        lines = lines[:-1]
    return '\n'.join(lines).strip()

last_lines_series = df['clean_text'].apply(get_last_text_line)
last_lines_series = last_lines_series.replace("", pd.NA).dropna()
last_line_frequencies = last_lines_series.value_counts()
frequent_last_lines = last_line_frequencies[last_line_frequencies > 1].index.tolist()

df['clean_text'] = df['clean_text'].apply(lambda x: remove_frequent_last_line(x, frequent_last_lines))

# %% [markdown]
# Проведена стандартная очистка текстовых данных:
# 1. Приведение к нижнему регистру
# 2. Удаление разметки (HTML/Markdown) и спецсимволов
# 3. Лемматизация и удаление стоп-слов
# 4. Очистка от ссылок (частый шаблон в конце постов)
# 
# Такая обработка унифицирует данные для последующего NLP-анализа, удаляя технический "шум" без потери смыслового содержания. Особое внимание уделено ссылкам - их массовое удаление исключает искажение статистик из-за повторяющихся элементов.

# %% [markdown]
# ### Топ-20 самых частых слов

# %%
all_words = ' '.join(df['clean_text']).split()
word_freq = Counter(all_words).most_common(20)

total_words = sum([w[1] for w in word_freq])
word_freq_normalized = [(w[0], w[1] / total_words * 100) for w in word_freq]

plt.figure(figsize=(10, 6))
sns.barplot(y=[w[0] for w in word_freq_normalized], x=[w[1] for w in word_freq_normalized], palette='rocket')
plt.title('Топ-20 самых частых слов', fontsize=14)
plt.xlabel('Процентное соотношение')
plt.ylabel('Слово')
plt.show()

# %% [markdown]
# После очистки данных от стоп-слов анализ частотности выявил характерные языковые паттерны. 
# 
# Анализ частотности слов выявил ключевые особенности текстов:
# 
# 1. Организационные маркеры ("подписаться", "канал") - требуют удаления как шаблонные элементы
# 2. Географические указатели ("россия", "москва") - отражают локальную специфику
# 3. Тематические термины ("правительство", "компания") - указывают на основные темы
# 4. Глаголы действия ("сообщать", "писать") - характерны для новостного стиля
# 
# **Дальнейшая работа требует:**
# - Дополнительной очистки от шаблонных фраз
# - Анализа устойчивых словосочетаний
# - Изучения распределения слов по категориям

# %%
stop.update(["это", "также", "подписаться", "который", "изза", "прислать", "ещё", "которые", "топор", "подписывайся", "mash", "shot", "live", "новостную", "кибертопор"])

df['clean_text'] = df['clean_text'].apply(lambda x: remove_stop_words(x, stop))

# %% [markdown]
# ### Анализ топ-слов по категориям

# %%
tfidf = TfidfVectorizer(max_features=50)
tfidf_matrix = tfidf.fit_transform(df['clean_text'])
tfidf_df = pd.DataFrame(tfidf_matrix.toarray(), columns=tfidf.get_feature_names_out())

fig, axes = plt.subplots(rows, cols, figsize=(14, rows * 4))
axes = axes.flatten()
for i, category in enumerate(categories):
    top_words = tfidf_df[df['category'] == category].mean().sort_values(ascending=False).head(8)
    
    sns.barplot(x=top_words.values, y=top_words.index, ax=axes[i], palette='rocket')
    axes[i].set_title(f"Топ-8 слов для категории: {category}")
    axes[i].set_xlabel('Среднее значение TF-IDF')
    axes[i].set_ylabel('Слова')

for j in range(i + 1, len(axes)):
    fig.delaxes(axes[j])

plt.tight_layout()
plt.show()

# %% [markdown]
# Анализ топ-слов по категориям показывает, что в категории "политика" преобладают термины, связанные с Россией и политическими событиями, а в "личном" — слова, указывающие на людей. В "финансах" часто упоминаются деньги , в "IT" — технические слова, такие как "python" и "данных". В категории "прочее" также встречаются слова, связанные с действиями и текущими событиями, как "сегодня" или "человек". В научных постах акцент на времени и возможностях, в рекламных — на деньгах и датах. В бизнес-контенте выделяются термины, связанные с компаниями и экономикой, а в постах о Москве преобладает географическая тематика. В целом, каждое слово соответствует тематике своей категории, будь то политика, финансы, технологии или другие области.

# %% [markdown]
# ### Анализ биграмм

# %%
cv2 = CountVectorizer(ngram_range=(2,2), max_features=50)
bigrams = cv2.fit_transform(df['clean_text'])
bigram_freq = pd.DataFrame(bigrams.toarray(), columns=cv2.get_feature_names_out()).sum().sort_values(ascending=False).head(30)
bigram_freq_normalized = bigram_freq / bigram_freq.sum() * 100

plt.figure(figsize=(12, 6))
sns.barplot(x=bigram_freq_normalized.index, y=bigram_freq_normalized.values, palette='rocket')
plt.title('Топ-30 самых частых биграмм', fontsize=14)
plt.xlabel('Биграмма')
plt.ylabel('Процентное соотношение')
plt.xticks(rotation=70)
plt.show()

# %% [markdown]
# Частотные биграммы четко соотносятся с несколькими ключевыми категориями. Финансовая тематика (finances) выражена сочетаниями вроде "млн рублей", "тыс рублей", "курс доллара", что логично для этой группы. Новости о политике и госструктурах (political) подтверждаются биграммами "владимир путин", "минобороны рф", "вс рф", а также "уголовное дело" и "возбуждено уголовное", которые могут относиться и к political, и к personal в случае криминальных происшествий.
# 
# Технологическая направленность (it, science) прослеживается в биграммах "data science", "читать vpn", "удалённо опыт", причем последнее может также попадать в business, если речь идет о удаленной работе. Упоминание "риа новости" и географических меток вроде "курской области" чаще относится к political или other, если контекст неясен.
# 
# Рекламные биграммы (advertisement) в этом списке выражены слабо, но сочетания вроде "статью зеркало" (возможно, ссылки на альтернативные источники) или "кликнуть bitly" (если бы присутствовали) могли бы указывать на эту категорию. Развлекательный контент (stuff) и gaming в текущей выборке биграмм практически не представлены.
# 
# **Для улучшения стоит:**
# 
# - Удалить общие фразы типа "стало известно", "данный момент", так как они не помогают в разграничении категорий.
# - Удалить биграммы вроде "читать статью" и "читать vpn" — они используются в некоторых каналах для добавления первоисточника.

# %%
bigrams_to_remove = {
    "стало известно", 
    "данный момент", 
    "читать статью", 
    "читать vpn",
    "риа новости"
}

def remove_bigrams(text: str, bigrams_to_remove: set) -> str:
    for bigram in bigrams_to_remove:
        if bigram in text:
            text = text.replace(bigram, "")
    return text.strip()

df['clean_text'] = df['clean_text'].apply(lambda x: remove_bigrams(x, bigrams_to_remove))

# %% [markdown]
# ### Анализ временной активности публикаций

# %%
df['weekday'] = df['date'].dt.strftime('%A')
df['hour'] = df['date'].dt.hour
df['weekday'] = df['date'].dt.day_name()

# %%
plt.figure(figsize=(10, 4))
sns.countplot(x='weekday', data=df, order=['Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday', 'Sunday'], palette='coolwarm')
plt.title('Распределение постов по дням недели')
plt.xlabel('День недели')
plt.ylabel('Количество постов')
plt.show()

# %%
plt.figure(figsize=(12, 4))
sns.countplot(x='hour', data=df, palette='coolwarm')
plt.title('Активность по часам', fontsize=14)
plt.xlabel('Час дня')
plt.ylabel('Количество постов')
plt.show()

# %%
plt.figure(figsize=(14, 5))
df.set_index('date').resample('D').size().plot()
plt.title('Частота публикаций по дням')
plt.xlabel('Дата')
plt.ylabel('Количество постов')
plt.grid(True)
plt.show()

# %%
heatmap_data = df.groupby(['weekday', 'hour', 'category']).size().reset_index(name='count')
pivot = heatmap_data.sort_values('weekday').pivot_table(index='category', columns='weekday', values='count', aggfunc='sum')

plt.figure(figsize=(12, 6))
sns.heatmap(pivot, cmap='coolwarm', linewidths=0.5)
plt.title("Распределение категорий по дням недели")
plt.xlabel("День недели")
plt.ylabel("Число постов")
plt.show()

# %%
pivot = heatmap_data.pivot_table(index='category', columns='hour', values='count', aggfunc='sum')

plt.figure(figsize=(12, 6))
sns.heatmap(pivot, cmap='coolwarm', linewidths=0.5)
plt.title("Распределение категорий по часам")
plt.xlabel("Час")
plt.ylabel("Число постов")
plt.show()

# %%
groups = [group['hour'].values for _, group in df.groupby('category')]
stat, p = kruskal(*groups)
print(f"Kruskal-Wallis H-statistic: {stat:.3f}, p-value: {p:.13f}")

# %% [markdown]
# Анализ временной структуры данных показал, что посты охватывают период с октября 2023 по октябрь 2024 года, с пиком активности в октябре 2024. Наибольшая активность публикаций наблюдается в утренние и дневные часы (с 5 до 19 часов), особенно в 7 утра, и чаще всего — по вторникам. Это указывает на ориентацию постинга на рабочие будни и утреннюю аудиторию.
# 
# Тепловые карты и временные графики показывают, что время публикации играет важную роль в классификации: например, IT-контент чаще публикуется в 7, 9 и 18 часов, а политические новости — с 7 до 10 и с 13 до 14 часов. При этом день недели оказывает менее выраженное влияние на различие между классами.
# 
# Статистический тест Kruskal–Wallis (H=83.238, p≈0.0000) подтвердил наличие значимых различий в распределении времени публикаций по категориям, что свидетельствует о разных "временных паттернах жизни" контента.

# %% [markdown]
# ### UMAP Визуализация категорий

# %%
model = SentenceTransformer("DeepPavlov/rubert-base-cased")

# %%
embeddings = model.encode(df['clean_text'].tolist())

umap_model = UMAP(n_components=2, random_state=42)
embeddings_umap = umap_model.fit_transform(embeddings)

tsne_model = TSNE(n_components=2, random_state=42, perplexity=30)
embeddings_tsne = tsne_model.fit_transform(embeddings)


fig, axs = plt.subplots(1, 2, figsize=(14, 6))

sns.scatterplot(x=embeddings_umap[:, 0], y=embeddings_umap[:, 1], 
                hue=df['category'], palette='tab20', s=10, ax=axs[0])
axs[0].set_title("UMAP по категориям")

sns.scatterplot(x=embeddings_tsne[:, 0], y=embeddings_tsne[:, 1], 
                hue=df['category'], palette='tab20', s=10, ax=axs[1], legend=False)
axs[1].set_title("t-SNE по категориям")

plt.tight_layout()
plt.show()

# %% [markdown]
# UMAP и tSNE показывает, что категории частично разделяются: "political", "science", "personal", "finances" и "business" образуют чёткие кластеры, а "weather" и "moscow" смешиваются, что говорит об их схожести. Так же мы можем видеть точки класса "other" на границах некоторых класетров, это говорит о том, что категория "other" при разметке датасета использовалась как метка, где трудно отличить тематику поста. Некоторые точки-выбросы могут быть аномалиями. В целом, модель улавливает различия, но для спорных категорий желательна доработка, либо уточнение признаков.

# %% [markdown]
# ### Сравнение LightGBM и RuBERT

# %%
unique_labels = df['category'].unique()
label_to_id = {label: idx for idx, label in enumerate(unique_labels)}
id_to_label = {idx: label for label, idx in label_to_id.items()}
target_names = [id_to_label[i] for i in sorted(id_to_label)]
df['category_id'] = df['category'].apply(lambda x: label_to_id[x])

df_small_balanced = df.groupby('category').sample(n=200, random_state=42)
X_train, X_val, y_train, y_val = train_test_split(
    df_small_balanced[['clean_text', 'hour']], df_small_balanced['category_id'], test_size=0.2, random_state=42, stratify=df_small_balanced['category_id']
)

# %%
tfidf = TfidfVectorizer(max_features=5000)
X_train_tfidf = tfidf.fit_transform(X_train['clean_text'])
X_val_tfidf = tfidf.transform(X_val['clean_text'])

X_train_final = hstack([X_train_tfidf, X_train['hour'].values.reshape(-1, 1)])
X_val_final = hstack([X_val_tfidf, X_val['hour'].values.reshape(-1, 1)])

lgb_train = lgb.Dataset(X_train_final, label=y_train)
lgb_eval = lgb.Dataset(X_val_final, label=y_val, reference=lgb_train)

params = {
    'objective': 'multiclass',
    'num_class': len(df_small_balanced['category_id'].unique()),
    'metric': 'multi_logloss',
    'boosting_type': 'gbdt',
    'learning_rate': 0.1,
    'num_leaves': 31,
    'verbosity': -1,
    'seed': 42
}

model_lgb = lgb.train(
    params,
    lgb_train,
    valid_sets=[lgb_train, lgb_eval],
    num_boost_round=100,
    callbacks=[lgb.early_stopping(stopping_rounds=10)]
)

# %%
predictions_lgb = model_lgb.predict(X_val_final)
predicted_labels_lgb = predictions_lgb.argmax(axis=1)
print(classification_report(y_val, predicted_labels_lgb, target_names=target_names))

# %%
class Dataset(torch.utils.data.Dataset):
    def __init__(self, texts, hours, labels, tokenizer, max_len=128):
        self.texts = texts
        self.hours = hours
        self.labels = labels
        self.tokenizer = tokenizer
        self.max_len = max_len

    def __len__(self):
        return len(self.texts)

    def __getitem__(self, idx):
        encoding = self.tokenizer(
            self.texts[idx],
            truncation=True,
            padding='max_length',
            max_length=self.max_len,
            return_tensors='pt'
        )
        return {
            'input_ids': encoding['input_ids'].squeeze(),
            'attention_mask': encoding['attention_mask'].squeeze(),
            'numeric_features': torch.tensor(self.hours[idx], dtype=torch.float),
            'labels': torch.tensor(self.labels[idx], dtype=torch.long)
        }

class CustomModel(torch.nn.Module):
    def __init__(self, model_name, num_labels):
        super().__init__()
        self.bert = AutoModelForSequenceClassification.from_pretrained(model_name, num_labels=num_labels).bert
        self.classifier = torch.nn.Linear(self.bert.config.hidden_size + 1, num_labels)
        self.num_labels = num_labels

    def forward(self, input_ids, attention_mask, numeric_features, labels=None):
        outputs = self.bert(input_ids=input_ids, attention_mask=attention_mask)
        pooled_output = outputs.pooler_output
        combined = torch.cat((pooled_output, numeric_features.unsqueeze(1)), dim=1)
        logits = self.classifier(combined)
        loss = None
        if labels is not None:
            loss_fct = torch.nn.CrossEntropyLoss()
            loss = loss_fct(logits.view(-1, self.num_labels), labels.view(-1))
        return {'loss': loss, 'logits': logits}

tokenizer = AutoTokenizer.from_pretrained("DeepPavlov/rubert-base-cased")
train_dataset = Dataset(X_train['clean_text'].tolist(), X_train['hour'].tolist(), y_train.tolist(), tokenizer)
val_dataset = Dataset(X_val['clean_text'].tolist(), X_val['hour'].tolist(), y_val.tolist(), tokenizer)

model_rubert = CustomModel("DeepPavlov/rubert-base-cased", num_labels=len(df_small_balanced['category_id'].unique()))
training_args = TrainingArguments(
    output_dir="./results",
    per_device_train_batch_size=8,
    per_device_eval_batch_size=8,
    num_train_epochs=3,
    logging_dir='./logs',
    do_eval=True,
    save_total_limit=1
)

def compute_metrics(pred):
    logits, labels = pred
    preds = logits.argmax(axis=-1)
    accuracy = (preds == labels).mean()
    f1 = f1_score(labels, preds, average="macro")
    return {"accuracy": accuracy, "f1": f1}

trainer = Trainer(
    model=model_rubert,
    args=training_args,
    train_dataset=train_dataset,
    eval_dataset=val_dataset,
    compute_metrics=compute_metrics
)

trainer.train()

# %%
predictions_rubert = trainer.predict(val_dataset)
predicted_labels_rubert = predictions_rubert.predictions.argmax(axis=-1)
true_labels = predictions_rubert.label_ids

print(classification_report(true_labels, predicted_labels_rubert, target_names=target_names))

# %%
fig, axes = plt.subplots(1, 2, figsize=(12, 5))

cm1 = confusion_matrix(y_val, predicted_labels_lgb)
sns.heatmap(cm1, annot=True, fmt='d', cmap='Blues', xticklabels=target_names, yticklabels=target_names, ax=axes[0])
axes[0].set_title(f'Confusion Matrix - LightGBM')
axes[0].set_xlabel('Predicted')
axes[0].set_ylabel('True')
axes[0].tick_params(axis='x', rotation=45)

cm2 = confusion_matrix(true_labels, predicted_labels_rubert)
sns.heatmap(cm2, annot=True, fmt='d', cmap='Blues', xticklabels=target_names, yticklabels=target_names, ax=axes[1])
axes[1].set_title(f'Confusion Matrix - RuBERT')
axes[1].set_xlabel('Predicted')
axes[1].set_ylabel('True')
axes[1].tick_params(axis='x', rotation=45)

plt.tight_layout()
plt.show()

# %% [markdown]
# На ограниченной выборке (по 200 примеров на каждый класс) модель LightGBM показала точность 58%, в то время как RuBERT достиг 78%. Это существенное улучшение указывает на высокую эффективность трансформеров в нашей задаче текстовой классификации, где важно учитывать контекст сообщений.
# 
# Результаты подтверждают, что модели на основе трансформеров (такие как RuBERT), обучающиеся на семантических связях в тексте, значительно превосходят традиционные ML-подходы при работе с текстами, где поверхностных признаков (например, отдельных слов или времени публикации) недостаточно для точной классификации.


