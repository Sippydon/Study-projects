package s21.bootcamp.tictactoe.web.model;

import lombok.Data;

@Data
public class WebModel {
    private String id;
    private String[][] board;
    private String winner;
    private Boolean cheater;
}
