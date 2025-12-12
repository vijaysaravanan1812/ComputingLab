1# Write your MySQL query statement below
2select customer_number  
3from Orders
4group by customer_number
5order by count(*) desc
6limit 1