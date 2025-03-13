def decrypt(ciphertext):
    n = len(ciphertext)
    ans = [''] * n  # 用于存放解密后的字符
    index = [0]  # 使用列表封装索引，确保在递归时可以更新

    def decrypt_helper(l, r):
        if l > r:
            return
        mid = (l + r) // 2  # 计算中间位置
        ans[mid] = ciphertext[index[0]]  # 取密文中的字符
        index[0] += 1  # 移动索引
        decrypt_helper(l, mid - 1)  # 递归处理左半部分
        decrypt_helper(mid + 1, r)  # 递归处理右半部分

    decrypt_helper(0, n - 1)
    return ''.join(ans)

# 读取输入
ciphertext = input().strip()
# 解密并输出
print(decrypt(ciphertext))