select person_order.order_date as action_date, person.name as person_name
from person_order
         inner join person
                    on person_order.person_id = person.id
intersect
select visit_date, person.name
from person_visits
         inner join person
                    on person_visits.person_id = person.id
order by action_date, person_name desc;
