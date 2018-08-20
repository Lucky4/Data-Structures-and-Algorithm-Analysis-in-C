# Huffman编码是贪婪算法的应用，称为文件压缩，构造trie树后，向左是0，向右是1。
# 这些字符代码的长度是否重要并不要紧，只要没有字符代码是别的字符代码的前缀即可，又叫做前缀码。
# 哈夫曼树根据集合中权值最小的两颗树构建一个新树。

class TreeNode(object):
    def __init__(self, weight, chr=''):
        self.weight = weight
        self.chr = chr
        self.left = None
        self.right = None


class Huffman(object):
    def __init__(self, encode_str):
        self.encode_str = encode_str
        self.chr_times_dict = {}

    def make_tree(self):
        # Count chr times.
        for i in self.encode_str:
            if i not in self.chr_times_dict:
                self.chr_times_dict[i] = 1
            else:
                self.chr_times_dict[i] += 1

        # Make chrs to TreeNode list.
        son_node_list = []
        for j in self.chr_times_dict:
            node = TreeNode(self.chr_times_dict[j], j)
            son_node_list.append(node)

        # Compare function.
        cmp = lambda x, y : 1 if x.weight > y.weight else -1

        # Make the huffman tree.
        while len(son_node_list) > 1:
            son_node_list.sort(cmp=cmp)
            son1 = son_node_list.pop(0)
            son2 = son_node_list.pop(0)
            son3 = TreeNode(son1.weight + son2.weight)
            son3.left = son1
            son3.right = son2
            son_node_list.append(son3)
        
        return son_node_list[0] # root

    def get_encode_res(self, root):
        res = {}
        for i in self.encode_str:
            l = []

            def get_encode_str(i, root, l):
                found = False
                if root.chr == i:
                    return True

                if not found and root.left != None:
                    l.append('0')
                    found = get_encode_str(i, root.left, l)

                if not found and root.right != None:
                    l.append('1')
                    found = get_encode_str(i, root.right, l)

                if not found:
                    l.pop()
                return found

            get_encode_str(i, root, l)
            l.reverse()
            res[i] = ''.join(l)
        return res


if __name__ == '__main__':
    try:
        while True:
            encode_str = raw_input().strip()
            if not encode_str:
                break
            
            h = Huffman(encode_str)
            tree = h.make_tree()
            encode = h.get_encode_res(tree)
            
            res = 0
            for i in encode:
                res += len(encode[i]) * h.chr_times_dict[i]
            print res
    except EOFError:
        pass
