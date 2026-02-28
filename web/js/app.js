(function bootstrapStickyBoard() {
  const board = document.getElementById("board");
  const addCardButton = document.getElementById("add-card-btn");
  const colorPicker = document.getElementById("card-color");

  if (!board || !addCardButton || !colorPicker) {
    return;
  }

  let cardCounter = 0;

  function createCard() {
    cardCounter += 1;

    const card = document.createElement("article");
    card.className = "card";
    card.style.left = `${40 + (cardCounter % 4) * 210}px`;
    card.style.top = `${40 + Math.floor(cardCounter / 4) * 170}px`;
    card.style.backgroundColor = colorPicker.value;
    card.style.setProperty("--angle", `${(Math.random() * 4 - 2).toFixed(2)}deg`);

    card.innerHTML = `
      <h3>Card ${cardCounter}</h3>
      <p>Connect this note to others in your board workflow.</p>
    `;

    board.appendChild(card);
  }

  addCardButton.addEventListener("click", createCard);

  createCard();
  createCard();
})();
