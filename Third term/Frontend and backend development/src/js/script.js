function showMessage(message) {
    console.log(message);
}

function logCurrentTime() {
    const now = new Date();
    const hours = String(now.getHours()).padStart(2, '0');
    const minutes = String(now.getMinutes()).padStart(2, '0');
    const seconds = String(now.getSeconds()).padStart(2, '0');
    console.log(`Текущее время: ${hours}:${minutes}:${seconds}`);
}

function changeBackgroundColor(color) {
    document.body.style.backgroundColor = color;
}

function resetBackgroundColor() {
    document.body.style.backgroundColor = "white";
}
  
function toggleVisibility(selector) {
    const element = document.querySelector(selector);
    if (element) {
        const currentDisplay = getComputedStyle(element).display;
        console.log(currentDisplay)
        element.style.display = currentDisplay === 'none' ? '' : 'none';
    }
}

function updateH1WithUTMTerm() {
    const urlParams = new URLSearchParams(window.location.search);
    const utmTerm = urlParams.get('utm_term');
    const h1 = document.querySelector('h1');
    if (h1) {
        if (utmTerm) {
            h1.textContent = utmTerm;
        }
    }
}

function handleH1Click() {
    alert("Вы кликнули на заголовок - так держать!");
}

function handlePClick(p) {
    console.log("d");
    p.style.transition = 'color 0.5s ease';
    p.style.color = 'lightblue';
}

function handleH1MouseOver() {
    const h1 = document.querySelector('h1');
    if (h1) {
        h1.style.transition = 'transform 0.3s ease';
        h1.style.transform = 'scale(1.1)';
    }
}

function handleH1MouseOut() {
    const h1 = document.querySelector('h1');
    if (h1) {
        h1.style.transition = 'transform 0.3s ease';
        h1.style.transform = 'scale(1)';
    }
}

function handleMouseOver() {
    const studentPhoto = document.querySelector('#student-photo');
    if (studentPhoto) {
        studentPhoto.style.transform = 'scale(1.1) rotate(15deg)';
        studentPhoto.style.transition = 'transform 0.3s ease';
    }
}

function handleMouseOut() {
    const studentPhoto = document.querySelector('#student-photo');
    if (studentPhoto) {
        studentPhoto.style.transform = 'scale(1) rotate(0deg)';
        studentPhoto.style.transition = 'transform 0.3s ease';
    }
}

function handlePhotoClick() {
    const studentPhoto = document.querySelector('#student-photo');
    if (studentPhoto) {
        studentPhoto.src = 'src/img/icon.jpg';
        studentPhoto.alt = 'Изображение любимого преподавателя';
    }
}

function handlePhotoDoubleClick() {
    alert("Не налегай, у меня не так много любимых преподавателей");
}

// ====================================================================================

showMessage("Скрипт загружен!");
logCurrentTime();

document.addEventListener("DOMContentLoaded", () => {
    resetBackgroundColor();
    changeBackgroundColor("lightblue");
    toggleVisibility(".page-info");

    const pElements = document.querySelectorAll('p');
    pElements.forEach((p) => {
        p.addEventListener('click', () => handlePClick(p));
    });

    const h1 = document.querySelector('h1');
    if (h1) {
        h1.addEventListener('click', handleH1Click);
        h1.addEventListener('mouseover', handleH1MouseOver);
        h1.addEventListener('mouseout', handleH1MouseOut);
    }

    const studentPhoto = document.querySelector('#student-photo');
    if (studentPhoto) {
        studentPhoto.addEventListener('mouseover', handleMouseOver);
        studentPhoto.addEventListener('mouseout', handleMouseOut);
        studentPhoto.addEventListener('click', handlePhotoClick);
        studentPhoto.addEventListener('dblclick', handlePhotoDoubleClick);
    }
});
