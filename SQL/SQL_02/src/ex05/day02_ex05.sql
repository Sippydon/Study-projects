select person.name
from person
where person.age > 25
  and person.gender = 'female'
order by person.name