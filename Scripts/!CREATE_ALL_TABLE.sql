USE BOOKS_MANAGEMENT_SYSTEM
CREATE TABLE CARD_INFO
(SNO INT PRIMARY KEY,
SUP INT NOT NULL ,
BS CHAR(50) ,
OverdueS CHAR(50) ,
OverdueP CHAR(50));

INSERT INTO CARD_INFO VALUES
(10001,3,'2','0',0),
(10002,3,'0','0',0),
(10003,3,'1','0',0),
(10004,3,'0','0',0),
(10005,3,'1','0',0),
(10006,3,'0','1',24),
(10007,3,'0','1',17);


CREATE TABLE STUDENT_INFO
(SNA CHAR(50),
SDE CHAR(50),
SSP CHAR(50),
SNO INT ,
PRIMARY KEY(SNA ,SNO));

INSERT INTO STUDENT_INFO
VALUES ('张三', '计算机科学系' ,'网络空间安全' , 10001 ),  
('李四', '计算机科学系' ,'网络空间安全' , 10002 ), 
('王艾力', '经济系' ,'国际贸易' , 10003 ), 
('钱宝波', '电子工程' ,'自动控制' , 10004 ), 
('郑弗', '电子工程' ,'自动控制' , 10005 ), 
('于罢', '电子工程' ,'数字电路' , 10006 ), 
('周何沃', '外语系' ,'俄语' , 10007 );


CREATE TABLE BOOKS_INFO
(BNA CHAR(20) NOT NULL ,
BNO CHAR(5) PRIMARY KEY,
BDA INT,
BPU CHAR(15),
BPL CHAR(10),
BorrowInfo CHAR(5) );

INSERT INTO BOOKS_INFO
VALUES ('数据结构 ',  'SJ001',  2018,'清华大学出版社 ',  '计科书架 ', '0'),
 ('数据结构 ',  'SJ002',  2018,'清华大学出版社',  '计科书架 ', '10001'),
 ('数据结构 ',  'SJ003',  2018,'清华大学出版社',  '计科书架 ', '0'),
 ('数据结构 ',  'SJ004',  2018,'清华大学出版社',  '计科书架 ', '0'),
 ('操作系统 ',  'CZ001',  2017,'北京大学出版社',  '计科书架 ', '0'),
 ('操作系统 ',  'CZ002',  2017,'北京大学出版社',  '计科书架 ', '0'),
 ('操作系统 ',  'CZ003',  2017,'北京大学出版社',  '计科书架 ', '0'),
 ('LINUX私房菜',  'LN001',  2014,'浙江大学出版社',  '计科书架 ', '10001'),
 ('LINUX私房菜',  'LN002',  2014,'浙江大学出版社',  '计科书架 ', '0'),
 ('信息安全法律基础',  'XX001',  2019,'人民大学出版社',  '人文书架 ', '10005'),
 ('信息安全法律基础',  'XX002',  2019,'人民大学出版社',  '人文书架 ', '0'),
 ('信息安全法律基础',  'XX003',  2019,'人民大学出版社',  '人文书架 ', '0'),
 ('数据库程序设计',  'SK001',  2018,'复旦大学出版社',  '人文书架 ', '10003'),
 ('数据库程序设计',  'SK002',  2018,'复旦大学出版社',  '人文书架 ', '0'),
 ('数据库程序设计',  'SK003',  2018,'复旦大学出版社',  '人文书架 ', '0'),
 ('数据库程序设计',  'SK004',  2018,'复旦大学出版社',  '人文书架 ', '0'),
 ('数据库程序设计',  'SK005',  2018,'复旦大学出版社',  '人文书架 ', '0');
 
 
 CREATE TABLE BOOKS_MAIN
(BNA CHAR(50) PRIMARY KEY,
BNU INT );

INSERT INTO BOOKS_MAIN VALUES ('数据结构', 10);
INSERT INTO BOOKS_MAIN VALUES ('操作系统', 10);
INSERT INTO BOOKS_MAIN VALUES ('LINUX的私房菜', 5);  
INSERT INTO BOOKS_MAIN VALUES ('信息安全法律基础', 4);
INSERT INTO BOOKS_MAIN VALUES ('数据库', 5);


CREATE TABLE BORROW_INFO
(SNO INT NOT NULL,
BNO CHAR(50) PRIMARY KEY,
BorrowTime CHAR(50) ,
ReturnTime CHAR(50) ,
Overdue CHAR(50))

INSERT INTO BORROW_INFO
VALUES (10001,'SJ002' ,'2019-07-12' , '2019-10-12','0'),
(10001,'LN001' ,'2019-07-07' , '2019-10-07','0'),
(10003,'SK001' ,'2019-08-15' , '2019-11-15','0'),
(10005,'XX001' ,'2019-09-01' , '2019-12-01','0');