package s21.bootcamp.tictactoe.datasource.service;

import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import s21.bootcamp.tictactoe.datasource.mappers.dataModelMapper;
import s21.bootcamp.tictactoe.datasource.model.dataModel;
import s21.bootcamp.tictactoe.datasource.repository.BoardRepository;
import s21.bootcamp.tictactoe.domain.model.domainModel;
import s21.bootcamp.tictactoe.domain.service.ServiceInterface;

import java.util.Map;
import java.util.NoSuchElementException;

@Service
@RequiredArgsConstructor
public class ServiceImpl implements ServiceInterface {
    private final BoardRepository gamesRepository;

    @Override
    public void getTurnMinimax(String gameId) {
        // Получаем текущую игру
        if (gamesRepository.getWinner(gameId) == null) {
            dataModel game = gamesRepository.getGame(gameId);
            if (game == null) {
                throw new IllegalArgumentException("Game with ID " + gameId + " not found.");
            }

            String[][] board = game.getBoard();

            int[] bestMove = findBestMove(board);
            if (bestMove != null) {
                board[bestMove[0]][bestMove[1]] = "O"; // Компьютер делает ход
                game.setBoard(board);
                gamesRepository.updateGame(gameId, game); // Обновляем доску
            }

            gamesRepository.setWinner(gameId, checkWinner(board));
        }
    }

    private int[] findBestMove(String[][] board) {
        int bestScore = Integer.MIN_VALUE;
        int[] move = null;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j].equals("")) { // Проверяем доступность клетки
                    board[i][j] = "O"; // Пробуем сделать ход 'О'
                    int score = minimax(board, 0, false); // Оцениваем текущий ход
                    board[i][j] = ""; // Отменяем ход

                    if (score > bestScore) {
                        bestScore = score;
                        move = new int[]{i, j}; // Сохраняем лучший ход
                    }
                }
            }
        }
        return move;
    }

    private int minimax(String[][] board, int depth, boolean isAITurn) {
        String winner = checkWinner(board); // Проверяем победителя
        if (winner != null) {
            if (winner.equals("O")) return 10 - depth; // Если победил компьютер
            if (winner.equals("X")) return depth - 10; // Если победил пользователь
            return 0; // Ничья
        }

        int bestScore;
        if (isAITurn) {
            bestScore = Integer.MIN_VALUE;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j].equals("")) {
                        board[i][j] = "O"; // Пробуем 'О'
                        int score = minimax(board, depth + 1, false);
                        board[i][j] = ""; // Отменяем ход
                        bestScore = Math.max(bestScore, score);
                    }
                }
            }
        } else {
            bestScore = Integer.MAX_VALUE;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j].equals("")) {
                        board[i][j] = "X"; // Пробуем 'X'
                        int score = minimax(board, depth + 1, true);
                        board[i][j] = ""; // Отменяем ход
                        bestScore = Math.min(bestScore, score);
                    }
                }
            }
        }
        return bestScore;
    }

    @Override
    public Boolean validate(String gameId, dataModel game) throws NoSuchElementException {
        int onlyOneChange = 0;
        boolean isValid = true;

        String[][] oldBoard = gamesRepository.getGame(gameId).getBoard();
        String[][] newBoard = game.getBoard();

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (oldBoard[i][j].equals("X") || oldBoard[i][j].equals("O")) {
                    switch (oldBoard[i][j]) {
                        case "X":
                            if (newBoard[i][j].equals("O")) {
                                isValid = false;
                            }
                            break;
                        case "O":
                            if (newBoard[i][j].equals("X")) {
                                isValid = false;
                            }
                    }
                }
                if (!oldBoard[i][j].equals(newBoard[i][j])) {
                    onlyOneChange++;
                }
                if (onlyOneChange > 1) {
                    isValid = false;
                }
            }
        }
        if (!isValid) {
            gamesRepository.setCheater(gameId);
        }
        return isValid;
    }

    @Override
    public String checkWinner(String[][] board) {
        for (int i = 0; i < 3; i++) {
            if (!board[i][0].equals("") && board[i][0].equals(board[i][1]) && board[i][1].equals(board[i][2])) {

                return board[i][0]; // Победитель в строке
            }
            if (!board[0][i].equals("") && board[0][i].equals(board[1][i]) && board[1][i].equals(board[2][i])) {
                return board[0][i]; // Победитель в столбце
            }
        }

        if (!board[0][0].equals("") && board[0][0].equals(board[1][1]) && board[1][1].equals(board[2][2])) {
            return board[0][0]; // Победитель на главной диагонали
        }

        if (!board[0][2].equals("") && board[0][2].equals(board[1][1]) && board[1][1].equals(board[2][0])) {
            return board[0][2]; // Победитель на побочной диагонали
        }

        // Проверка на ничью
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j].equals("")) return null; // Если есть пустые клетки, игра продолжается
            }
        }

        return "Tie"; // Ничья
    }

    @Override
    public dataModel getModel() {
        dataModel model = dataModelMapper.INSTANCE.toDataModel(new domainModel());
        gamesRepository.insertGame(model.getGameId(), model);
        return model;
    }

    @Override
    public dataModel makeMove(String gameId, dataModel game) throws NoSuchElementException {
            if (gamesRepository.getWinner(gameId) != null) {
                throw new NoSuchElementException("Game with ID " + gameId + " is already finished.");
            }
            gamesRepository.updateGame(gameId, game);
            getTurnMinimax(gameId);
            return gamesRepository.getGame(gameId);
    }

    @Override
    public void delete(String gameId) {
        gamesRepository.deleteGame(gameId);
    }

    @Override
    public Map<String, dataModel> getAllGames() {
        return gamesRepository.getAllGames();
    }
}
