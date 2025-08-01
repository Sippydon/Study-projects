const baseUrl = 'http://localhost:8080/game/'; // Базовый URL для серверных запросов

// Состояние всех активных игр
const activeGames = {};

// Функция добавления логов
function addLog(message) {
    const logDiv = document.getElementById('log');
    const logMessage = document.createElement('p');
    logMessage.textContent = message;
    logDiv.appendChild(logMessage);
    logDiv.scrollTop = logDiv.scrollHeight;
}

// Функция инициализации новой игры
async function startNewGame() {
    try {
        const response = await fetch(`${baseUrl}start`);
        if (!response.ok) throw new Error('Failed to start a new game.');
        const game = await response.json();

        // Рендер новой игры
        renderGameBoard(game);
        addLog(`Game started with ID: ${game.id}`);
    } catch (error) {
        console.error(error);
        addLog('Error: Unable to start a new game.');
    }
}

// Функция удаления игры
async function deleteGame(gameId) {
    try {
        const response = await fetch(`${baseUrl}${gameId}`, { method: 'DELETE' });
        if (!response.ok) throw new Error('Failed to delete the game.');
        document.getElementById(`game-container-${gameId}`).remove(); // Удаляем визуально
        delete activeGames[gameId]; // Удаляем из состояния
        addLog(`Game with ID: ${gameId} was deleted.`);
    } catch (error) {
        console.error(error);
        addLog(`Error: Unable to delete game with ID: ${gameId}`);
    }
}

// Функция рендеринга новой игровой доски
// function renderGameBoard(game) {
//     const { id, board } = game;
//     activeGames[id] = board;
//
//     const gameArea = document.getElementById('game-area');
//
//     // Создаем контейнер для игры
//     const gameContainer = document.createElement('div');
//     gameContainer.id = `game-container-${id}`;
//     gameContainer.className = 'game-container';
//     gameContainer.innerHTML = `
//         <h2>Game ID: ${id}</h2>
//         <div class="game-board" id="game-board-${id}"></div>
//         <button class="delete-game-button" data-game-id="${id}">Delete Game</button>
//     `;
//     gameArea.appendChild(gameContainer);
//
//     // Инициализируем игровую доску
//     initBoard(id, board);
//
//     // Добавляем обработчик для кнопки удаления
//     gameContainer.querySelector('.delete-game-button').addEventListener('click', () => deleteGame(id));
// }
function renderGameBoard(game) {
    const { id, board } = game;

    // Если ID игры некорректен, пропускаем
    if (!id || !Array.isArray(board) || board.length < 3) {
        console.warn(`Skipping invalid game data: ${JSON.stringify(game)}`);
        return;
    }

    // Если доска уже отрисована в DOM, не пересоздаём её
    if (document.getElementById(`game-container-${id}`)) {
        console.log(`Game with ID ${id} is already rendered.`);
        return;
    }

    activeGames[id] = board; // Добавляем в локальное состояние

    const gameArea = document.getElementById('game-area');

    // Создаём новый контейнер для игры
    const gameContainer = document.createElement('div');
    gameContainer.id = `game-container-${id}`;
    gameContainer.className = 'game-container';
    gameContainer.innerHTML = `
        <h2>Game ID: ${id}</h2>
        <div class="game-board" id="game-board-${id}"></div>
        <button class="delete-game-button" data-game-id="${id}">Delete Game</button>
    `;
    gameArea.appendChild(gameContainer);

    // Инициализируем игровую доску
    initBoard(id, board);

    // Добавляем обработчик для кнопки удаления
    gameContainer.querySelector('.delete-game-button').addEventListener('click', () => deleteGame(id));
}

// Инициализация игровой доски
function initBoard(gameId, board) {
    const boardContainer = document.getElementById(`game-board-${gameId}`);
    boardContainer.innerHTML = ''; // Очистить, если уже существует

    for (let row = 0; row < 3; row++) {
        for (let col = 0; col < 3; col++) {
            const cell = document.createElement('div');
            cell.className = 'cell';
            cell.dataset.row = row;
            cell.dataset.col = col;

            if (board[row][col] !== null) {
                cell.textContent = board[row][col];
                cell.classList.add('taken');
            }

            cell.addEventListener('click', () => makeMove(gameId, row, col));
            boardContainer.appendChild(cell);
        }
    }
}

// Совершение хода
async function makeMove(gameId, row, col) {
    const board = activeGames[gameId];
    if (board[row][col]) return; // Если ячейка занята, игнорируем

    board[row][col] = 'X'; // Обновляем локально
    try {
        const response = await fetch(`${baseUrl}${gameId}`, {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({ id: gameId, board, winner: null, cheater: false })
        });
        if (!response.ok) throw new Error();

        const updatedGame = await response.json();
        activeGames[gameId] = updatedGame.board; // Обновляем доску игры
        updateBoard(gameId, updatedGame.board);

        if (updatedGame.winner) addLog(`Game ${gameId} Over! Winner: ${updatedGame.winner}`);
    } catch (error) {
        console.error(error);
        addLog(`Error: Move failed for game ${gameId}`);
    }
}

// Обновление доски
function updateBoard(gameId, board) {
    const boardContainer = document.getElementById(`game-board-${gameId}`);
    const cells = boardContainer.querySelectorAll('.cell');
    cells.forEach(cell => {
        const row = parseInt(cell.dataset.row, 10);
        const col = parseInt(cell.dataset.col, 10);
        cell.textContent = board[row][col];
        if (board[row][col]) cell.classList.add('taken');
    });
}

// Получение и отображение всех активных игр
// async function getActiveGames() {
//     try {
//         const response = await fetch(`${baseUrl}info`);
//         if (!response.ok) throw new Error('Failed to fetch games info.');
//
//         const games = await response.json();
//         Object.values(games).forEach(renderGameBoard);
//     } catch (error) {
//         console.error(error);
//         addLog('Error: Unable to fetch active games.');
//     }
// }

// Обработчики глобальных кнопок
document.getElementById('start-new-game').addEventListener('click', startNewGame);


