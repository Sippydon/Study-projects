with mens as (select person.id,
                     person.name
              from person
              where person.gender = 'male'
                and person.address in ('Moscow', 'Samara')
              )

select mens.name
from mens
    join person_order on person_order.person_id = mens.id
    join menu on person_order.menu_id = menu.id
where menu.pizza_name in ('pepperoni pizza', 'mushroom pizza')
order by mens.name desc