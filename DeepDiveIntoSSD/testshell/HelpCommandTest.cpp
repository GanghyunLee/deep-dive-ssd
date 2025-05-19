#include "HelpView.h"
#include "ICommandMapper.h"
#include "gmock/gmock.h"
#include <ostream>

#include "HelpCommand.h"

using namespace std;
using namespace testing;

class HelpCommandTestFixture : public Test
{
public:
	~HelpCommandTestFixture() override = default;

public:
	std::shared_ptr<HelpCommand> helpCommand = make_shared<HelpCommand>();
};

TEST_F(HelpCommandTestFixture, HelpCommandMustGenerateHelpView)
{
	std::shared_ptr<IView> view = helpCommand->Execute();
	EXPECT_TRUE(typeid(*view) == typeid(std::shared_ptr<HelpView>));
}