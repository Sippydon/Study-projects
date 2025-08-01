select person.name as person_name,
       m.pizza_name as pizza_name,
       pi.name as pizzeria_name
from person
         join person_order po on po.person_id = person.id
         join menu m on m.id = po.menu_id
         join pizzeria pi on m.pizzeria_id = pi.id
order by person_name, pizza_name, pizzeria_name;
