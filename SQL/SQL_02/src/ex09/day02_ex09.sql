with womens as (select person.id, person.name, person_order.menu_id
                from person
                         join person_order on person.id = person_order.person_id
                where person.gender = 'female')

select womens.name as name
from womens
         join menu on womens.menu_id = menu.id
where menu.pizza_name = 'cheese pizza'
intersect
select womens.name as name
from womens
         join menu on womens.menu_id = menu.id
where menu.pizza_name = 'pepperoni pizza'
order by name
