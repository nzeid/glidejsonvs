# GlideJsonVs

This codebase is dedicated to roughly testing the performance of GlideJson. Emphasis on roughly. The speed of encoding and parsing isn't everything, but it's a decent starting point.

### Intel(R) Core(TM) i3 CPU 530 @2.93GHz

||Parsing (us)|Encoding (us)|
|:---|---:|---:|
|[GlideJson](https://github.com/nzeid/glidejson)|431563|386674|
|[JSON for Modern C++](https://github.com/nlohmann/json)|770675|564016|
|[JsonCpp](https://github.com/open-source-parsers/jsoncpp)|1019472|1230270|
|[cJSON](https://github.com/DaveGamble/cJSON)|221684|492799|
|[RapidJSON](https://github.com/Tencent/rapidjson)|222590|203233|

## Some Takeaways

- Neither "Json for Modern C++" nor JsonCpp are interested in beating speed tests, but they are very widely used. They serve as an upper bound for performance.
- cJSON and RapidJSON are also popular but very fast. They implement barebones wrappers for JSON structures and use linked lists for containers. This has performance implications when the resulting JSON structures are heavily manipulated.

## Contributing

Please communicate changes over this project's GitLab/GitHub pages. Bear in mind that the GitLab/GitHub pages are merely mirrors of a separate "official" repository. Any accepted changes will get due authorship and credit.

- [https://github.com/nzeid/glidejsonvs](https://github.com/nzeid/glidejsonvs)
- [https://gitlab.com/nzeid/glidejsonvs](https://gitlab.com/nzeid/glidejsonvs)

## License

Copyright (c) 2020 Nader G. Zeid

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see [https://www.gnu.org/licenses/gpl.html](https://www.gnu.org/licenses/gpl.html).
