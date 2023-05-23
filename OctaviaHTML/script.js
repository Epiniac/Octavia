


function slider(anything) {
  document.querySelector('.one').src = anything;
};

let menu = document.querySelector('#menu-icon');
let navbar = document.querySelector('.navbar');

menu.onclick = () => {
  menu.classList.toggle('bx-x');
  navbar.classList.toggle('open');
}

$(document).ready(function () {
  $(window).scroll(function () {
    if ($(window).scrollTop() + $(window).height() == $(document).height()) {
      $('header').addClass('hidden');
    } else {
      $('header').removeClass('hidden');
    }
  });
});

const reviewForm = document.getElementById('review-form');
const reviewsSection = document.querySelector('.reviews');

reviewForm.addEventListener('submit', (event) => {
  event.preventDefault();

  const name = document.getElementById('name').value;
  const rating = document.getElementById('rating').value;
  const review = document.getElementById('review').value;

  const reviewItem = document.createElement('div');
  reviewItem.classList.add('review');
  reviewItem.innerHTML = `
    <h4>${name}</h4>
    <div class="rating">${'★'.repeat(rating)}${'☆'.repeat(5 - rating)}</div>
    <p>${review}</p>
  `;

  reviewsSection.appendChild(reviewItem);

  reviewForm.reset();
});

// Get the height of the footer
var footerHeight = document.querySelector('.footer').offsetHeight;

// Set the bottom padding of the content to be equal to the height of the footer
document.querySelector('.content').style.paddingBottom = footerHeight + 'px';


// Blur the background image
const background = document.querySelector('.background-image');
background.style.filter = 'blur(5px)';

// Get the form and overlay elements
const form = document.querySelector('form');
const overlay = document.querySelector('.overlay');

// Open the form when the page loads
window.onload = function () {
  overlay.style.display = 'block';
  form.style.display = 'block';
  document.body.style.overflow = 'hidden'; // Hide scrollbar
}

// Close the form when the overlay is clicked
overlay.addEventListener('click', function () {
  overlay.style.display = 'none';
  form.style.display = 'none';
  document.body.style.overflow = 'auto'; // Show scrollbar
});

// Prevent clicks inside the form from closing it

//Transcription



