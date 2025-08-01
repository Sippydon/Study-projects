package s21.bootcamp.tictactoe.datasource.model;

import lombok.Data;

@Data
public class dataModel {
    private final String gameId;
    private String[][] board;
    private String winner = null;
    private Boolean cheater;
}
