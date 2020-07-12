USE BOOKS_MANAGEMENT_SYSTEM
CREATE TABLE STUDENT_INFO
(SNA CHAR(50),
SDE CHAR(50),
SSP CHAR(50),
SNO INT ,
PRIMARY KEY(SNA ,SNO))



INSERT INTO STUDENT_INFO
VALUES ('张三', '计算机科学系' ,'网络空间安全' , 10001 ),  
('李四', '计算机科学系' ,'网络空间安全' , 10002 ), 
('王艾力', '经济系' ,'国际贸易' , 10003 ), 
('钱宝波', '电子工程' ,'自动控制' , 10004 ), 
('郑弗', '电子工程' ,'自动控制' , 10005 ), 
('于罢', '电子工程' ,'数字电路' , 10006 ), 
('周何沃', '外语系' ,'俄语' , 10007 );
