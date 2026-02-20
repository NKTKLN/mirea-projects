String? validateUsername(String value) {
  if (value.isEmpty) {
    return "Имя не может быть пустым";
  }

  final RegExp nameRegExp = RegExp(r'^[A-Za-zА-Яа-яЁё]+(?: [A-Za-zА-Яа-яЁё]+)*$');

  if (!nameRegExp.hasMatch(value) || value.length < 2) {
    return "Разрешены только буквы и пробелы (мин. 2 символа)";
  }

  return null;
}
