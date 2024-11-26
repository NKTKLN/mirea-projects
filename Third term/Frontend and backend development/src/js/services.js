// Modal
// Получаем модальное окно и кнопки открытия
const modal = document.getElementById("modal");
const openModalButtons = document.querySelectorAll("#openModalBtn");
const closeBtn = document.getElementsByClassName("close")[0];

// Функция для открытия модального окна
openModalButtons.forEach((button) => {
  button.onclick = function () {
    const selected = button.getAttribute("data-modal");
    const option = document.getElementById(selected);

    // Сбрасываем выделение всех опций перед установкой новой
    document
      .querySelectorAll(
        "[id^='business'], [id^='corp'], [id^='shop'], [id^='landing'], [id^='blog'], [id^='portfolio']"
      )
      .forEach((opt) => {
        opt.removeAttribute("selected");
      });

    // Устанавливаем "selected" для выбранной опции
    option.setAttribute("selected", "selected");

    // Открываем модальное окно
    modal.style.display = "flex";
  };
});

// Функция для закрытия модального окна
closeBtn.onclick = function () {
  modal.style.display = "none";
  resetSelection();
};

// Закрытие модального окна при клике вне его области
window.onclick = function (event) {
  if (event.target === modal) {
    modal.style.display = "none";
    resetSelection();
  }
};

// Сброс выбора опций
function resetSelection() {
  document
    .querySelectorAll(
      "[id^='business'], [id^='corp'], [id^='shop'], [id^='landing'], [id^='blog'], [id^='portfolio']"
    )
    .forEach((opt) => {
      opt.removeAttribute("selected");
    });
}

// Form
const formData = {
  name: '',
  email: '',
  phone: '',
  date: '',
  comment: '',
  printData: function () {
    console.log(`
Имя: ${this.name}
E-mail: ${this.email}
Телефон: ${this.phone}
Дата: ${this.date}
Комментарий: ${this.comment}
    `);
  }
};

function submitForm(event) {
  event.preventDefault();

  const nameInput = document.querySelector('#name');
  const emailInput = document.querySelector('#email');
  const phoneInput = document.querySelector('#phone');
  const dateInput = document.querySelector('#date');
  const commentInput = document.querySelector('#comment');

  if (!nameInput.value.trim() || !emailInput.value.trim() || !commentInput.value.trim()) {
    alert('Поля "Имя", "E-mail" и "Комментарий" обязательны для заполнения.');
    return;
  }

  const phoneRegex = /^\+7 \(\d{3}\) \d{3}-\d{2}-\d{2}$/;
  if (!phoneRegex.test(phoneInput.value.trim())) {
    alert('Телефон должен содержать только цифры.');
    return;
  }

  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  if (!emailRegex.test(emailInput.value.trim())) {
    alert('Некорректный формат E-mail.');
    return;
  }

  formData.name = nameInput.value.trim();
  formData.email = emailInput.value.trim();
  formData.phone = phoneInput.value.trim();
  formData.date = dateInput.value.trim();
  formData.comment = commentInput.value.trim();

  formData.printData();

  const modal = document.getElementById("modal");
  modal.style.display = "none";

  const successMessage = document.getElementById('successMessage');
  successMessage.classList.add('show');
  setTimeout(() => {
    successMessage.classList.remove('show');
  }, 3000);
}

const form = document.querySelector('form');
if (form) {
  form.addEventListener('submit', submitForm);
}

