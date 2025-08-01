select coalesce(pers.name, '-') as person_name,
       tmp.visit_date           as visit_date,
       coalesce(pi.name, '-')   as pizzeria_name
from (select *
      from person_visits
      where visit_date between '2022-01-01' and '2022-01-03') as tmp
         full join person pers on tmp.person_id = pers.id
         full join pizzeria pi on tmp.pizzeria_id = pi.id
order by person_name, visit_date, pizzeria_name;


