package s21.bootcamp.tictactoe.datasource.repository;

import org.springframework.stereotype.Repository;
import s21.bootcamp.tictactoe.datasource.model.dataModel;

import java.util.*;

@Repository
public class RepositoryImpl implements BoardRepository {
    private final Map<String, dataModel> games = Collections.synchronizedMap(new HashMap<>());

    public RepositoryImpl() {
    }



    @Override
    public dataModel getGame(String id) throws NoSuchElementException {
        if (!games.containsKey(id)) {
            throw new NoSuchElementException("Game with ID " + id + " does not exist.");
        }
        return games.get(id);
    }

    @Override
    public void insertGame(String id, dataModel boardDTO) {
        games.put(id, boardDTO);
    }

    @Override
    public void updateGame(String id, dataModel dataModel) throws NoSuchElementException {
        if (!games.containsKey(id)) {
            throw new NoSuchElementException("Game with ID " + id + " does not exist.");
        }
        games.put(id, dataModel);
    }

    @Override
    public void deleteGame(String id) throws NoSuchElementException {
        if (!games.containsKey(id)) {
            throw new NoSuchElementException("Game with ID " + id + " does not exist.");
        }
        games.remove(id);
    }

    @Override
    public Map<String, dataModel> getAllGames() {
        return games;
    }

    @Override
    public void setWinner(String id, String winner) {
        games.get(id).setWinner(winner);
    }

    @Override
    public String getWinner(String id) {
        return games.get(id).getWinner();
    }

    @Override
    public void setCheater(String id) {
        games.get(id).setCheater(true);
    }

    @Override
    public Boolean getCheater(String id) {
        return games.get(id).getCheater();
    }


}
