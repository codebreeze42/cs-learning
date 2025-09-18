import csv
import itertools
import sys

PROBS = {

    # Unconditional probabilities for having gene
    "gene": {
        2: 0.01,
        1: 0.03,
        0: 0.96
    },

    "trait": {

        # Probability of trait given two copies of gene
        2: {
            True: 0.65,
            False: 0.35
        },

        # Probability of trait given one copy of gene
        1: {
            True: 0.56,
            False: 0.44
        },

        # Probability of trait given no gene
        0: {
            True: 0.01,
            False: 0.99
        }
    },

    # Mutation probability
    "mutation": 0.01
}


def main():

    # Check for proper usage
    if len(sys.argv) != 2:
        sys.exit("Usage: python heredity.py data.csv")
    people = load_data(sys.argv[1])

    # Keep track of gene and trait probabilities for each person
    probabilities = {
        person: {
            "gene": {
                2: 0,
                1: 0,
                0: 0
            },
            "trait": {
                True: 0,
                False: 0
            }
        }
        for person in people
    }

    # Loop over all sets of people who might have the trait
    names = set(people)
    for have_trait in powerset(names):

        # Check if current set of people violates known information
        fails_evidence = any(
            (people[person]["trait"] is not None and
             people[person]["trait"] != (person in have_trait))
            for person in names
        )
        if fails_evidence:
            continue

        # Loop over all sets of people who might have the gene
        for one_gene in powerset(names):
            for two_genes in powerset(names - one_gene):

                # Update probabilities with new joint probability
                p = joint_probability(people, one_gene, two_genes, have_trait)
                update(probabilities, one_gene, two_genes, have_trait, p)

    # Ensure probabilities sum to 1
    normalize(probabilities)

    # Print results
    for person in people:
        print(f"{person}:")
        for field in probabilities[person]:
            print(f"  {field.capitalize()}:")
            for value in probabilities[person][field]:
                p = probabilities[person][field][value]
                print(f"    {value}: {p:.4f}")


def load_data(filename):
    """
    Load gene and trait data from a file into a dictionary.
    File assumed to be a CSV containing fields name, mother, father, trait.
    mother, father must both be blank, or both be valid names in the CSV.
    trait should be 0 or 1 if trait is known, blank otherwise.
    """
    data = dict()
    with open(filename) as f:
        reader = csv.DictReader(f)
        for row in reader:
            name = row["name"]
            data[name] = {
                "name": name,
                "mother": row["mother"] or None,
                "father": row["father"] or None,
                "trait": (True if row["trait"] == "1" else
                          False if row["trait"] == "0" else None)
            }
    return data


def powerset(s):
    """
    Return a list of all possible subsets of set s.
    """
    s = list(s)
    return [
        set(s) for s in itertools.chain.from_iterable(
            itertools.combinations(s, r) for r in range(len(s) + 1)
        )
    ]


def get_parent_gene_count(parent, one_gene, two_genes):
    """获取父母的基因数量"""
    if parent in one_gene:
        return 1
    elif parent in two_genes:
        return 2
    else:
        return 0


def calcutate_inheritance_probability(child_genes, mother_genes, father_genes):
    # 根据父母的基因数量计算有特定基因数量的孩子患病的可能性
    mutation = PROBS["mutation"]
    no_mutation = 1 - mutation

    # 从母亲获取基因的概率
    if mother_genes == 2:
        p_from_mother = no_mutation
    elif mother_genes == 1:
        p_from_mother = 0.5 * no_mutation + 0.5 * mutation
    else:
        p_from_mother = mutation

    # 从父亲获取基因的概率
    if father_genes == 2:
        p_from_father = no_mutation
    elif father_genes == 1:
        p_from_father = 0.5 * no_mutation + 0.5 * mutation
    else:
        p_from_father = mutation

    if child_genes == 2:
        return p_from_mother * p_from_father
    elif child_genes == 1:
        return p_from_mother * (1 - p_from_father) + (1 - p_from_mother) * p_from_father
    else:
        return (1 - p_from_mother) * (1 - p_from_father)


def joint_probability(people, one_gene, two_genes, have_trait):
    """
    Compute and return a joint probability.

    The probability returned should be the probability that
        * everyone in set `one_gene` has one copy of the gene, and
        * everyone in set `two_genes` has two copies of the gene, and
        * everyone not in `one_gene` or `two_gene` does not have the gene, and
        * everyone in set `have_trait` has the trait, and
        * everyone not in set` have_trait` does not have the trait.
    """
    joint_p = 1.0

    for person in people:
        # 确定每个人的基因数
        if person in one_gene:
            gene_count = 1
        elif person in two_genes:
            gene_count = 2
        else:
            gene_count = 0
        # 确定是否有症状
        has_trait = person in have_trait

        # 获取person的数据
        person_data = people[person]
        mother = person_data["mother"]
        father = person_data["father"]
        # 根据基因数量计算概率
        if mother is None and father is None:
            # 没有父母信息
            gene_p = PROBS["gene"][gene_count]
        else:
            # 有父母信息
            mother_genes = get_parent_gene_count(mother, one_gene, two_genes)
            father_genes = get_parent_gene_count(father, one_gene, two_genes)
            
            gene_p = calcutate_inheritance_probability(gene_count, mother_genes, father_genes)

        # 根据基因数量计算概率
        trait_p = PROBS["trait"][gene_count][has_trait]

        # 计算联合概率
        joint_p *= gene_p * trait_p
    return joint_p

def update(probabilities, one_gene, two_genes, have_trait, p):
    """
    Add to `probabilities` a new joint probability `p`.
    Each person should have their "gene" and "trait" distributions updated.
    Which value for each distribution is updated depends on whether
    the person is in `have_gene` and `have_trait`, respectively.
    """
    for person in probabilities:
        # 更新基因概率
        if person in one_gene:
            probabilities[person]["gene"][1] += p
        elif person in two_genes:
            probabilities[person]["gene"][2] += p
        else:
            probabilities[person]["gene"][0] += p
        # 更新症状概率
        if person in have_trait:
            probabilities[person]["trait"][True] += p
        else:
            probabilities[person]["trait"][False] += p

def normalize(probabilities):
    """
    Update `probabilities` such that each probability distribution
    is normalized (i.e., sums to 1, with relative proportions the same).
    """
    for person in probabilities:
        # 标准化基因分布
        gene_sum = sum(probabilities[person]["gene"].values())
        if gene_sum > 0:
            for gene_count in probabilities[person]["gene"]:
                probabilities[person]["gene"][gene_count] /= gene_sum
        # 标准化症状分布
        trait_sum = sum(probabilities[person]["trait"].values())
        if trait_sum > 0:
            for trait_value in probabilities[person]["trait"]:
                probabilities[person]["trait"][trait_value]/=trait_sum


if __name__ == "__main__":
    main()
