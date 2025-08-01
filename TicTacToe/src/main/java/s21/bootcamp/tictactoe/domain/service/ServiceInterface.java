package s21.bootcamp.tictactoe.domain.service;

import s21.bootcamp.tictactoe.datasource.model.dataModel;

import java.util.Map;
import java.util.NoSuchElementException;

@org.springframework.stereotype.Service
public interface ServiceInterface {
    public void getTurnMinimax(String gameId) throws NoSuchElementException;

    Boolean validate(String gameId, dataModel game) throws NoSuchElementException;

    public String checkWinner(String[][] board);
    public dataModel getModel();

    dataModel makeMove(String gameId, dataModel game) throws NoSuchElementException;

    public void delete(String gameId);
    Map<String, dataModel> getAllGames();
}
