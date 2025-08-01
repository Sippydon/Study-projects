select pizzeria.name
from pizzeria
where pizzeria.id not in (select person_visits.pizzeria_id from person_visits);

select pizzeria.name
from pizzeria
where not exists (select pizzeria_id from person_visits where pizzeria.id = person_visits.pizzeria_id);