package s21.bootcamp.tictactoe.web.controller;

import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import s21.bootcamp.tictactoe.datasource.model.dataModel;
import s21.bootcamp.tictactoe.datasource.service.ServiceImpl;
import s21.bootcamp.tictactoe.domain.service.ServiceInterface;
import s21.bootcamp.tictactoe.web.mapper.WebModelMapper;
import s21.bootcamp.tictactoe.web.model.WebModel;

import java.util.Map;

@RestController
@RequiredArgsConstructor
@RequestMapping("game/")
public class WebController {
    private final ServiceInterface service;

    @Autowired
    public WebController(ServiceImpl service) {
        this.service = service;
    }

    @GetMapping(value = "/start")
    public ResponseEntity<WebModel> create() {
        WebModel model = WebModelMapper.INSTANCE.toWebModel(service.getModel());
        return ResponseEntity.ok(model);
    }

    @PostMapping(value = "/{gameId}")
    public ResponseEntity<?> update(@PathVariable(name = "gameId") String gameId, @RequestBody WebModel webModel) {
        try {
            if (service.validate(gameId, WebModelMapper.INSTANCE.toDataModel(webModel))) {
                return ResponseEntity.ok(WebModelMapper.INSTANCE.toWebModel(service.makeMove(gameId, WebModelMapper.INSTANCE.toDataModel(webModel))));
            } else {
                return errorHandling(new Exception("Game with ID " + gameId + " is cheated."));
            }
        } catch (Exception e) {
            return errorHandling(e);
        }
    }
    
    @DeleteMapping(value = "/{gameId}")
    public ResponseEntity<?> delete(@PathVariable(name = "gameId") String gameId) {
        try {
            service.delete(gameId);
            return ResponseEntity.ok().build();
        } catch (Exception e) {
            return errorHandling(e);
        }
    }

    @GetMapping(value="info")
    public ResponseEntity<Map<String, dataModel>> getGames() {
        return service.getAllGames().isEmpty() ? ResponseEntity.noContent().build() : ResponseEntity.ok(service.getAllGames());
    }

    private ResponseEntity<?> errorHandling(Exception e) {
        return ResponseEntity.badRequest().body(e.getMessage());
    }

}
