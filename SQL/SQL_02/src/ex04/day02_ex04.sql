select pizzas.pizza_name as pizza_name,
       pizzeria.name as pizzeria_name,
       pizzas.price as price
from (
    select *
    from menu
    where menu.pizza_name in ('mushroom pizza', 'pepperoni pizza')
     ) as pizzas
join pizzeria on pizzas.pizzeria_id = pizzeria.id
order by pizza_name, pizzeria_name;

