import os
import zipfile
from reportlab.platypus import SimpleDocTemplate, Paragraph, Spacer, Table, TableStyle
from reportlab.lib.styles import getSampleStyleSheet
from reportlab.pdfbase import pdfmetrics
from reportlab.pdfbase.ttfonts import TTFont

base_dir = r"C:\Users\NKTKLN\Desktop\MIREA\PoCS\practice_13\Data\Incoming"
os.makedirs(base_dir, exist_ok=True)

pdfmetrics.registerFont(TTFont("Arial", r"C:\Windows\Fonts\arial.ttf"))

styles = getSampleStyleSheet()
style = styles["Normal"]
style.fontName = "Arial"
style.fontSize = 12
style.leading = 18

cases = [
    (
        "case_20260420.zip",
        ["ID: CASE-1001", "Клиент: ООО Вектор", "Дата: 20.04.2026"],
        ["ID: CASE-1001", "Клиент: ООО Вектор", "Комментарий: Диагностика серверного оборудования"]
    ),
    (
        "case_20260421.zip",
        ["ID: CASE-1002", "Клиент: ИП Сидоров А.В.", "Дата: 21.04.2026"],
        ["ID: CASE-1002", "Клиент: ИП Сидоров А.В.", "Комментарий: Проверка лицензий ПО"]
    ),
    (
        "case_20260422.zip",
        ["ID: CASE-1003", "Клиент: АО Прогресс", "Дата: 22.04.2026"],
        ["ID: CASE-1003", "Клиент: АО Прогресс", "Комментарий: Аудит информационной безопасности"]
    )
]

def create_pdf(path, lines):
    doc = SimpleDocTemplate(path)
    elements = []

    for line in lines:
        elements.append(Paragraph(line, style))
        elements.append(Spacer(1, 6))

    elements.append(Spacer(1, 20))

    table = Table([
        ["№", "Статус"],
        ["1", "Принято"]
    ])

    table.setStyle(TableStyle([
        ("FONTNAME", (0, 0), (-1, -1), "Arial"),
        ("FONTSIZE", (0, 0), (-1, -1), 12),
        ("GRID", (0, 0), (-1, -1), 1, "black"),
    ]))

    elements.append(table)
    doc.build(elements)

for zip_name, form_lines, request_lines in cases:
    temp_dir = os.path.join(base_dir, "temp")
    os.makedirs(temp_dir, exist_ok=True)

    form_pdf = os.path.join(temp_dir, "form.pdf")
    request_pdf = os.path.join(temp_dir, "request.pdf")

    create_pdf(form_pdf, form_lines)
    create_pdf(request_pdf, request_lines)

    zip_path = os.path.join(base_dir, zip_name)

    if os.path.exists(zip_path):
        os.remove(zip_path)

    with zipfile.ZipFile(zip_path, "w", zipfile.ZIP_DEFLATED) as z:
        z.write(form_pdf, "form.pdf")
        z.write(request_pdf, "request.pdf")

    os.remove(form_pdf)
    os.remove(request_pdf)
    os.rmdir(temp_dir)

print("Готово")