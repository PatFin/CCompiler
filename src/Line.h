#pragma once

namespace Model
{
    class Line
    {
        protected:
            int lineNumber;
        public:
            Line(int l);
            Line(const Line&);
            int getLine();
	    virtual ~Line();
    };
}
