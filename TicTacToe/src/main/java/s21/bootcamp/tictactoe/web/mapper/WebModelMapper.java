package s21.bootcamp.tictactoe.web.mapper;

import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.factory.Mappers;
import s21.bootcamp.tictactoe.datasource.model.dataModel;
import s21.bootcamp.tictactoe.web.model.WebModel;

@Mapper
public interface WebModelMapper {
    WebModelMapper INSTANCE = Mappers.getMapper(WebModelMapper.class);
    @Mapping(source = "gameId", target = "id")
    WebModel toWebModel(dataModel dataModel);
    @Mapping(source = "id", target = "gameId")
    dataModel toDataModel(WebModel webModelMapper);
}
