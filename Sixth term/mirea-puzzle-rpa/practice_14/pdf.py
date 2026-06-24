import os
import zipfile
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont

base_dir = r"C:\Users\NKTKLN\Desktop\MIREA\PoCS\practice_14\Data\Incoming_Persons"
os.makedirs(base_dir, exist_ok=True)

pdfmetrics.registerFont(TTFont("Arial", r"C:\Windows\Fonts\arial.ttf"))

styles = getSampleStyleSheet()
style = styles["Normal"]
style.fontName = "Arial"
style.fontSize = 10
style.leading = 18

cases = [
    (
        "person_20260421_100000.zip",
        "Фамилия: Иванов; Имя: Алексей; Отчество: Сергеевич; Серия: 4510; Номер: 567891",
        "ИНН: 770812345670",
        "СНИЛС: 112-233-445 95"
    ),
    (
        "person_20260421_103000.zip",
        "Фамилия: Петрова; Имя: Марина; Отчество: Викторовна; Серия: 4608; Номер: 123456",
        "ИНН: 781245678901",
        "СНИЛС: 111-222-333-45"
    ),
    (
        "person_20260421_110000.zip",
        "Фамилия: Смирнов; Имя: Дмитрий; Отчество: Андреевич; Серия: 4507; Номер: 778899",
        "ИНН: 540987654321",
        "СНИЛС: 98765432101"
    )
]

def create_pdf(path, text):
    doc = SimpleDocTemplate(path)
    elements = [
        Paragraph(text, style),
        Spacer(1, 12)
    ]
    doc.build(elements)

for zip_name, passport_text, inn_text, snils_text in cases:
    temp_dir = os.path.join(base_dir, "temp")
    os.makedirs(temp_dir, exist_ok=True)

    passport_pdf = os.path.join(temp_dir, "passport.pdf")
    inn_pdf = os.path.join(temp_dir, "inn.pdf")
    snils_pdf = os.path.join(temp_dir, "snils.pdf")

    create_pdf(passport_pdf, passport_text)
    create_pdf(inn_pdf, inn_text)
    create_pdf(snils_pdf, snils_text)

    zip_path = os.path.join(base_dir, zip_name)

    if os.path.exists(zip_path):
        os.remove(zip_path)

    with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as z:
        z.write(passport_pdf, "passport.pdf")
        z.write(inn_pdf, "inn.pdf")
        z.write(snils_pdf, "snils.pdf")

    os.remove(passport_pdf)
    os.remove(inn_pdf)
    os.remove(snils_pdf)
    os.rmdir(temp_dir)

print("Готово")
