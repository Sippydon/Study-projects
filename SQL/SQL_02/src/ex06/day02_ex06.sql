select menu.pizza_name as pizza_name,
       pizzeria.name   as pizzeria_name
from menu
         join person_order on menu.id = person_order.menu_id
         join person on person_order.person_id = person.id
         join pizzeria on menu.pizzeria_id = pizzeria.id
where person.name in ('Denis', 'Anna')
order by pizza_name, pizzeria_name;