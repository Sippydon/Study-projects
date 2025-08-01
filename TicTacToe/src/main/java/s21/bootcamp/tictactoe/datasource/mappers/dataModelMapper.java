package s21.bootcamp.tictactoe.datasource.mappers;

import org.mapstruct.Mapper;
import org.mapstruct.factory.Mappers;
import s21.bootcamp.tictactoe.datasource.model.dataModel;
import s21.bootcamp.tictactoe.domain.model.domainModel;

@Mapper
public interface dataModelMapper {
    dataModelMapper INSTANCE = Mappers.getMapper(dataModelMapper.class);

    dataModel toDataModel(domainModel domainModel);
    domainModel toDomainModel(dataModel boardDTO);
}
