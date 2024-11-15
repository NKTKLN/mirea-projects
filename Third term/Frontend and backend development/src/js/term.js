const secondSemesterTopics = [
    "Базовое бэкенд-приложение",
    "HTTP-запросы",
    "JSON и работа с ним",
    "HTTP-ответы",
    "Проектирование API",
    "Роутинг и его настройка",
    "NoSQL базы данных",
    "Обеспечение авторизации и доступа пользователей",
    "Работа сторонних сервисов уведомления и авторизации",
    "Основы ReactJS",
    "Работа с компонентами динамической DOM",
    "Использование хуков в React",
    "Основы микросервисной архитектуры",
    "Разработка классических модулей веб-приложений",
    "Разработка классических модулей веб-приложений"
];

function changeToSecondSemester() {
    const tableBody = document.querySelector("#semester-table");
  
    tableBody.innerHTML = '';
  
    secondSemesterTopics.forEach((topic, index) => {
        const row = document.createElement('tr');
        row.innerHTML = `
    <tr>
        <td class="text-center">${index + 1}</td>
        <td class="text-center">${topic}</td>
        <td class="text-center">
        <img src="src/img/checkbox-false.png" alt="checkbox-false" class="checkbox" />
        </td>
        <td class="text-center">
        <img src="src/img/checkbox-false.png" alt="checkbox-false" class="checkbox" />
        </td>
    </tr>
        `;
        tableBody.appendChild(row);
    });
}

function changeTableDisplay() {
    const table = document.querySelector('#lecture-table');
    const tableBtn = document.querySelector('#show-lecture-table-btn');
    if (table && tableBtn) {
        table.style.transition = 'opacity 1s ease-in-out';
        table.style.display = '';
        tableBtn.style.display = 'none';
        setTimeout(() => {
            table.style.opacity = '1';
        }, 1);
    }
}

document.getElementById('second-semester-btn').addEventListener('click', changeToSecondSemester);
document.getElementById('show-lecture-table-btn').addEventListener('click', changeTableDisplay);
