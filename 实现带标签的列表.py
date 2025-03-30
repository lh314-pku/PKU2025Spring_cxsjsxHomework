exit = None
class TaggedList:  #元素带标签的列表
# 在此处补充你的代码
    def __init__(self, a, b):
        self.elements = a
        self.tags = b
        self.tag_int = {tag: i for i, tag, in enumerate(b)}
        # 建立了标签到下标的映射
    
    def __len__(self):
        return len(self.elements)
        # 返回数据列表的长度
    
    def __getitem__(self, key):
        if isinstance(key, int):
            return self.elements[key]
        elif isinstance(key, str):
            return self.elements[self.tag_int[key]]
    # 根据下标/标签返回值

    def __setitem__(self, key, value):
        if isinstance(key, int):
            self.elements[key] = value
        elif isinstance(key, str):
            self.elements[self.tag_int[key]] = value

    def __str__(self):
        pairs =[f"{self.tags[i]}:{self.elements[i]}"for i in range(len(self.elements))]
        return ",".join(pairs)+","
a = TaggedList([70,80,90,100],["语文","数学","英语","物理"])
print(len(a),78 in a, 80 in a) #>>4 False True
print(str(a)) #>>语文:70,数学:80,英语:90,物理:100,
print(a[0],a['数学']) #>>70 80   标签也可以作为下标访问元素
a[1] = a['物理'] = 85
print(a) #>>语文:70,数学:85,英语:90,物理:85,