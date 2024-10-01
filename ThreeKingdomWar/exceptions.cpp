#include "exceptions.h"

UnknownTokenError::UnknownTokenError()
{
	set_error_message(new BaseMessage(
		"UnknownTokenError",
		{
			{"line", "unknown"}
		}
	)
	);
}

UnknownTokenError::UnknownTokenError(int pointer)
{
	set_error_message(new BaseMessage(
			"UnknownTokenError",
			{
				{"line", std::to_string(pointer)}
			}
		)
	);
}

UnknownExpressionError::UnknownExpressionError()
{
	set_error_message(new BaseMessage(
			"UnknownExpressionError",
			{
				{"line", "unknown"}
			}
		)
	);
}

UnknownExpressionError::UnknownExpressionError(int pointer)
{
	set_error_message(new BaseMessage(
			"UnknownExpressionError",
			{
				{"line", std::to_string(pointer)}
			}
		)
	);
}

ListError::ListError()
{
	set_error_message(new BaseMessage(
			"ListError",
			{
				{"line", "unknown"}
			}
		)
	);

}

ListError::ListError(int pointer)
{
	set_error_message(new BaseMessage(
			"ListError",
			{
				{"line", std::to_string(pointer)}
			}
		)
	);
}

StatementError::StatementError()
{
	set_error_message(new BaseMessage(
			"StatementError",
			{
				{"line", "unknown"}
			}
		)
	);
}

StatementError::StatementError(int pointer)
{
	set_error_message(new BaseMessage(
			"StatementError",
			{
				{"line", std::to_string(pointer)}
			}
		)
	);
}