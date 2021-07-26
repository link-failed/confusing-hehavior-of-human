#一年级数据清洗练习生

import xlrd #用于操作excel
from sklearn.feature_extraction.text import CountVectorizer #用于快速创建词典

data = xlrd.open_workbook("vector.xls")
table_r = data.sheets()[0] #取出excel的第一张表

text = ""

for i in range(1, 10): #实际range是整个excel的长度
    if table_r.cell_type(i, 35) == 1: #判断单元格的格式是否是String
        names = table_r.cell(i, 35).value.split('+') #此前应处理好excel，保证'+'是唯一分隔符
        for name in names:
            name += " " #用作分词标志（停用词
            text += name
# print(text)

# 建立词典的时候，一篇文章是一个列表，列表里每个字符串代表的是一个词语
# 所以该字符串应位于列表中
text = text.split('&') #字符串转列表的一个方法；括号中可以是任意不出现在文本中的字符

# 实例化CountVectorizer对象
# analyzer 参数默认‘word’, 会自动过滤单字'char_wb'
# 所以要特别注意列表里是“切除术”还是'切','除','术'
vectorizer = CountVectorizer()
vectorizer.fit(text)
print('词典为',vectorizer.vocabulary_)

#借助json实现对字典的保存与读取，比较美观；但没有何时的分行，看起来其实还是不方便
f = open('dictionary.txt','w')
f.write(str(vectorizer.vocabulary_))
f.close()
