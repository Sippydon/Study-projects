select p_o.order_date as order_date,
       p.name || ' (age:' || p.age || ')' as person_information
from person_order as p_o (id_n, id)
natural join public.person p
order by order_date, person_information;
