function toggleTheme() {
    const body = document.body;
    const icon = document.getElementById('theme-icon');

    if (!icon) return;

    body.classList.toggle('dark-theme');

    const theme = body.classList.contains('dark-theme') ? 'dark' : 'light';
    localStorage.setItem('theme', theme);

    icon.classList.remove('fa-sun', 'fa-moon');
    icon.classList.add(theme === 'dark' ? 'fa-moon' : 'fa-sun');
}
function applySavedTheme() {
    const savedTheme = localStorage.getItem('theme') || 'light';
    const body = document.body;
    const icon = document.getElementById('theme-icon');

    if (!icon) return;

    if (savedTheme === 'dark') {
        body.classList.add('dark-theme');
        icon.classList.remove('fa-sun');
        icon.classList.add('fa-moon');
    } else {
        body.classList.remove('dark-theme');
        icon.classList.remove('fa-moon');
        icon.classList.add('fa-sun');
    }
}
window.toggleTheme = toggleTheme;