var grid = [
  [3, 4, 5],
  [6, 7, 8],
  [9, 10, 11]
];
var turn = 1;
var duringTransition = false;

function select(x, y, obj) {
  if ([1, 2].includes(grid[x][y]) || duringTransition) return false;
  let src = "";
  if (turn == 1) {
    src = "circle.svg";
  } else {
    src = "triangle.svg";
  }

  obj.src = src;

  grid[x][y] = turn;

  duringTransition = true;

  let animation = obj.animate({
    opacity: [0.0, 1.0],
    transform: [
      'scale(1.5)',
      'scale(1.0)'
    ],
    easing: 'cubic-bezier(0.76,-0.36, 0.28, 1.59)',
  }, {
    duration: 400,
    fill: "forwards",
    iterations: 1,
  });


  animation.finished.then(() => {
    if (check()) {
      win();
    } else {
      changeTurn();

      if (turn == 1) turn = 2;
      else turn = 1;
    }

    duringTransition = false;

  });
}

// window.onload = () => {
//   showDialog("dialog-win");
// }

function win() {
  let winner = "triângulo";
  let winnerColor = "yellow";
  if (turn == 1) {
    winner = "círculo";
    winnerColor = "cyan";
  }
  document.querySelector("#winner-target").innerHTML = winner;
  document.querySelector("#winner-target").classList.add(winnerColor);
  showDialog("dialog-win");
}

function showDialog(id) {
  document.querySelector(".overlay").style.display = "block";
  document.querySelector("#" + id).style.display = "block";
  document.querySelector(".overlay").style.opacity = 1;
}

function gameLocked() {
  showDialog("dialog-tie");
}

function check() {
  let lock = true;
  for (let i = 0; i < 3; i++)
    for (let j = 0; j < 3; j++) {
      if (![1, 2].includes(grid[i][j])) {
        lock = false;
        break;
      }
    }
  for (let i = 0; i < 3; i++) {
    if (grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2]) return true;
    if (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i]) return true;
  }
  if (grid[0][0] == grid[1][1] && grid[0][0] == grid[2][2]) return true;
  if (grid[0][2] == grid[1][1] && grid[0][2] == grid[2][0]) return true;

  if (lock) gameLocked();
  return false;
}

function changeTurn() {
  let currentTurn = document.querySelector(".spinner");
  let direction = "";
  if (currentTurn.classList.contains("turn-player-2")) {
    direction = "reverse";
    currentTurn.classList.remove("turn-player-2");
    currentTurn.classList.add("turn-player-1");
  } else {
    direction = "normal";
    currentTurn.classList.remove("turn-player-1");
    currentTurn.classList.add("turn-player-2");
  }
  currentTurn.animate({
    transform: [
      'translateY(0px)',
      'translateY(-40px)'
    ],
    easing: 'cubic-bezier(0.76,-0.36, 0.28, 1.59)',
  }, {
    duration: 400,
    direction: direction,
    fill: "forwards",
    iterations: 1,
  });
}
