select g_s :: date as missing_date
from (select person_visits.visit_date
      from person_visits
      where person_visits.person_id = 1
         or person_visits.person_id = 2) as p_v
         right join generate_series('2022-01-01' :: date, '2022-01-10', '1 day') as g_s
                    on p_v.visit_date = g_s
where p_v.visit_date is null
order by g_s;