//  2006-2008 (c) Viva64.com Team
//  2008-2017 (c) OOO "Program Verification Systems"

#ifndef PVS_STUDIO_FREE_COMMENTS_COMMENTS_H
#define PVS_STUDIO_FREE_COMMENTS_COMMENTS_H

#include <string>
#include <vector>
#include <sstream>

namespace PvsStudioFreeComments
{
  struct Comment
  {
    Comment() = default;

    Comment(const char* t) : text(t), lines(0)
    {
      std::string line;
      std::istringstream stream(t);
      while (std::getline(stream, line))
      {
        addLine(line.data(), line.data() + line.length());
      }
    }

    bool addLine(const char *begin, const char *end)
    {
      size_t width = 0;

      while (begin != end && isspace(*begin))
      {
        width += (*begin == '\t' ? 4 : 1);
        ++begin;
      }

      if (width >= 80)
      {
        return false;
      }

      while (begin != end && isspace(*(end - 1)))
      {
        --end;
      }

      if (begin != end)
      {
        ++lines;
        if (!trimmedText.empty())
        {
          trimmedText += ' ';
        }
        trimmedText.append(begin, end);
      }

      return true;
    }

    std::string text;
    std::string trimmedText;
    size_t lines;
  };

  extern const std::vector<Comment> Comments;
  bool HasAnyComment(const char* buf);
}

#endif

