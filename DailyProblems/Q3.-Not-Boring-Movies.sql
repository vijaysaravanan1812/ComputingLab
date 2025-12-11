1# Write your MySQL query statement below
2select id, movie, description, rating
3from Cinema
4where id % 2 <> 0 AND description <> 'boring'
5order by rating desc