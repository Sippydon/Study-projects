select menu.pizza_name
from menu
union
select menu.pizza_name
from menu
order by pizza_name DESC