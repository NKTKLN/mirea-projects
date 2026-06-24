const form = document.getElementById('login_form');
const error = document.getElementById('error');

form.addEventListener('submit', async (e) => {
  e.preventDefault();

  const login = document.getElementById('login').value;
  const password = document.getElementById('password').value;

  const response = await fetch('/login', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json'
    },
    body: JSON.stringify({ login, password })
  });

  const data = await response.json();

  if (data.success) {
    window.location.href = '/dashboard';
    return;
  }

  error.textContent = data.message;
  error.classList.remove('hidden');
});