package s21.bootcamp.tictactoe.datasource.repository;

import s21.bootcamp.tictactoe.datasource.model.dataModel;

import java.util.Map;
import java.util.NoSuchElementException;

public interface BoardRepository {
    public dataModel getGame(String id) throws NoSuchElementException;
    public void insertGame(String id, dataModel dataModel);
    public void updateGame(String id, dataModel dataModel) throws NoSuchElementException;
    public void deleteGame(String id) throws NoSuchElementException;
    public Map<String, dataModel> getAllGames();
    public void setWinner(String id, String winner);
    public String getWinner(String id);
    public void setCheater(String id);
    public Boolean getCheater(String id);
}
