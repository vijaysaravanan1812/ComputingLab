1# Write your MySQL query statement below
2select class
3from Courses
4group by class
5having count(*) >= 5
6order by count(*) desc;
7
8
9