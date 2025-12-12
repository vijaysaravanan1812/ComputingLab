1# Write your MySQL query statement below
2select date_format(trans_date, '%Y-%m') as month, country,
3 count(*) as trans_count, 
4 sum(case when state = 'approved' then 1 else 0 end) as approved_count,             sum(amount) as trans_total_amount,
5 sum(case when state = 'approved' then amount else 0 end) approved_total_amount
6from Transactions
7group by  date_format(trans_date, '%Y-%m'),  country