select name as object_name
from (
    select name
    from person
    order by name) as pn
union all
select pizza_name
from (
    select pizza_name
    from menu
    order by pizza_name) as mpn;
