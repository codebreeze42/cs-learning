import os
import random
import re
import sys

# 阻尼系数
DAMPING = 0.85
# 样本数量
SAMPLES = 10000


def main():
    if len(sys.argv) != 2:
        sys.exit("Usage: python pagerank.py corpus")
    # 解析html文件，返回字典（页面，链接页面的集合）
    corpus = crawl(sys.argv[1])
    # 估算每个页面的pagerank，返回字典
    # 采样法
    ranks = sample_pagerank(corpus, DAMPING, SAMPLES)
    print(f"PageRank Results from Sampling (n = {SAMPLES})")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")
    # 迭代公式法
    ranks = iterate_pagerank(corpus, DAMPING)
    print(f"PageRank Results from Iteration")
    for page in sorted(ranks):
        print(f"  {page}: {ranks[page]:.4f}")


def crawl(directory):
    """
    Parse a directory of HTML pages and check for links to other pages.
    Return a dictionary where each key is a page, and values are
    a list of all other pages in the corpus that are linked to by the page.
    """
    pages = dict()

    # Extract all links from HTML files
    for filename in os.listdir(directory):
        if not filename.endswith(".html"):
            continue
        with open(os.path.join(directory, filename)) as f:
            contents = f.read()
            links = re.findall(r"<a\s+(?:[^>]*?)href=\"([^\"]*)\"", contents)
            pages[filename] = set(links) - {filename}

    # Only include links to other pages in the corpus
    for filename in pages:
        pages[filename] = set(
            link for link in pages[filename]
            if link in pages
        )

    return pages

# 接下来选择页面的概率
def transition_model(corpus, page, damping_factor):
    """
    Return a probability distribution over which page to visit next,
    given a current page.

    With probability `damping_factor`, choose a link at random
    linked to by `page`. With probability `1 - damping_factor`, choose
    a link at random chosen from all pages in the corpus.
    """
    # 获取所有页面
    all_pages = list(corpus.keys())
    n = len(all_pages)
    # 初始化概率分布，每个页面都有基础概率(1-d)/N
    probabilities = {p: (1 - damping_factor) / n for p in all_pages}
    # 获取当前页面的出链
    links = corpus[page]
    # 如果有出链
    if links:
        # 添加额外的概率
        additional_prob = damping_factor / len(links)
        for link in links:
            probabilities[link] += additional_prob
    # 没有出链
    else:
        additional_prob = damping_factor / n
        for p in all_pages:
            probabilities[p] += additional_prob
    return probabilities


def sample_pagerank(corpus, damping_factor, n):
    """
    Return PageRank values for each page by sampling `n` pages
    according to transition model, starting with a page at random.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    # 初始化计数器
    page_counts = {page: 0 for page in corpus}

    # 随机选择一个样本
    current_page = random.choice(list(corpus.keys()))
    page_counts[current_page] += 1

    # 生成剩余的样本
    for _ in range(n - 1):
        # 获取当前页面的转移概率
        probabilities = transition_model(corpus, current_page, damping_factor)

        # 根据概率分布选择下一个页面
        pages = list(probabilities.keys())
        weights = list(probabilities.values())
        current_page = random.choices(pages,weights=weights, k=1)[0]

        # 更新计数器
        page_counts[current_page] += 1

    # 计算pagerank
    pageranks = {page: count / n for page, count in page_counts.items()}
    return pageranks

def iterate_pagerank(corpus, damping_factor):
    """
    Return PageRank values for each page by iteratively updating
    PageRank values until convergence.

    Return a dictionary where keys are page names, and values are
    their estimated PageRank value (a value between 0 and 1). All
    PageRank values should sum to 1.
    """
    n = len(corpus)
    # 初始化PageRank值
    pageranks = {page: 1 / n for page in corpus}

    # 创建字典，记录哪些页面链接到当前页面
    incoming_links = {page: set() for page in corpus}
    for page, links in corpus.items():
        if not links:
            for target_page in corpus:
                incoming_links[target_page].add(page)
        else:
            for link in links:
                incoming_links[link].add(page)

    # 迭代直到收敛
    changed = True
    while changed:
        changed =False
        new_pageranks = {}

        for page in corpus:
            # 计算随机跳转部分
            random_part = (1 - damping_factor) / n
            # 计算链接部分
            link_part = 0
            for linking_page in incoming_links[page]:
                num_links = len(corpus[linking_page])
                if num_links == 0:
                    num_links = n
                link_part += pageranks[linking_page] / num_links
            link_part *= damping_factor

            # 新的pagerank值
            new_rank = random_part + link_part
            new_pageranks[page] = new_rank

            # 检查是否收敛
            if abs(new_rank - pageranks[page]) > 0.001:
                changed = True

        # 更新pagerank值
        pageranks = new_pageranks

    return pageranks


if __name__ == "__main__":
    main()
