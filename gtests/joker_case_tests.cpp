#include "gtest/gtest.h"
#include "Corasick.h"

namespace {

    vector<int> Resault(const string& text, const string pattern, const char joker) {
       Bohr bohr;
       bohr.add_parts_to_bohr(pattern, joker);
       bohr.find_all_pos(text);
       bohr.joker_case_results(text.size(), pattern.size());
       return bohr.GetJokerCaseResaults();
    }
    
    void comparator(vector<int> v1, vector<int> v2) {
        for (size_t i = 0; i < v1.size(); ++i) {
            EXPECT_EQ(v1[i], v2[i]);
        }
    }
    
    struct JokerCaseTest
    {
        string text;
    	string pattern;
    	char joker;
    	vector<int> expected_indexes;
    };
    
    class JokerCaseTests : public ::testing::TestWithParam<JokerCaseTest>
    {
    public:
    
    	virtual void SetUp() override {
    	    _indexes = Resault(GetParam().text, GetParam().pattern, GetParam().joker);
    	}
        virtual void TearDown() override { }
    
    protected:
    
        vector<int> _indexes;
    };
    
    INSTANTIATE_TEST_CASE_P(DefaultCases, JokerCaseTests,
    ::testing::Values(
        JokerCaseTest{"ACT", "A$", '$', {1}},
    	JokerCaseTest{"AACTAG", "A$", '$', {1, 2, 5}},
    	JokerCaseTest{"AAAAATTTCGGGAAAA", "A&&", '&', {1, 2, 3, 4, 5 , 13, 14}},
    	JokerCaseTest{"AAAAATTTCGGGAAAA", "A##", '#', {1, 2, 3, 4, 5 , 13, 14}}
    ));
    
    INSTANTIATE_TEST_CASE_P(NoPatternCases, JokerCaseTests,
    ::testing::Values(
        JokerCaseTest{"ACTGTN", "CC$", '$', {}},
    	JokerCaseTest{"AACTAG", "A#A", '#', {}}
    ));
    
    TEST_P(JokerCaseTests, PSTest) {
        ASSERT_EQ(GetParam().expected_indexes.size(), _indexes.size());
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}