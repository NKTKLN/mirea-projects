// Scroll 

const scrollToTopBtn = document.getElementById("scrollToTopBtn");

scrollToTopBtn.onclick = function () {
  window.scrollTo({
    top: 0,
    behavior: "smooth"
  });
};

// Navigation button
const toggleNavigationBtn = document.getElementById('toggleNavigationBtn');
const pageNavigation = document.getElementById('pageNavigation');

toggleNavigationBtn.addEventListener('click', () => {
  pageNavigation.classList.toggle('active');
  toggleNavigationBtn.classList.toggle('active');
});

// Burger button
const burgerMenu = document.getElementById('burgerMenu');
const headerNav = document.getElementById('headerNav');

burgerMenu.addEventListener('click', () => {
  headerNav.classList.toggle('active');
});

// Url color
const currentPage = window.location.pathname.split("/").pop();
const navLinks = document.querySelectorAll(".header-navigation-link");

navLinks.forEach(link => {
  if (link.getAttribute("href") === currentPage) {
    link.classList.add("active");
  }
});
