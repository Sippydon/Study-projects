package s21.bootcamp.tictactoe.domain.model;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;

import java.util.Arrays;
import java.util.UUID;

@Data
public class domainModel {
    private String gameId;
    private String[][] board;
    
    public domainModel() {
        this.board = new String[3][3];
        Arrays.stream(this.board).forEach(row -> {Arrays.fill(row,"");});
        this.gameId  = UUID.randomUUID().toString();
//        this.gameId = "123456789";
    }
}
