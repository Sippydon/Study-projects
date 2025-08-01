select p_o.order_date as order_date,
       p.name || ' (age:' || p.age || ')' as person_information
from person_order as p_o
join person p on p_o.person_id = p.id
order by order_date, person_information;