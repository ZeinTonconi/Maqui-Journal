from pathlib import Path
import re
import shutil
import subprocess
import sys


# ============================================================
# CONFIGURATION
# ============================================================

ROOT = Path(__file__).resolve().parent

CODE_DIR = ROOT / "code"
OUTPUT_DIR = ROOT / "output"

TEX_FILE = OUTPUT_DIR / "team-book.tex"
PDF_FILE = OUTPUT_DIR / "team-book.pdf"

# Page layout
FONT_SIZE = "6.2pt"
LINE_HEIGHT = "6.9pt"
MARGIN = "0.42cm"
COLUMNS = 3


# ============================================================
# CATEGORY ORDER
# ============================================================

CATEGORIES = {
    "01_implementation": "Implementation",
    "02_data_structures": "Data Structures",
    "03_graph": "Graph",
    "04_trees": "Trees",
    "05_strings": "Strings",
    "06_math": "Math",
    "07_geometry": "Geometry",
    "08_dp": "Dynamic Programming",
    "09_advanced": "Advanced",
}


# ============================================================
# LATEX ESCAPING
# ============================================================

def latex_escape(text):
    replacements = {
        "\\": r"\textbackslash{}",
        "&": r"\&",
        "%": r"\%",
        "$": r"\$",
        "#": r"\#",
        "_": r"\_",
        "{": r"\{",
        "}": r"\}",
        "~": r"\textasciitilde{}",
        "^": r"\textasciicircum{}",
    }

    return "".join(replacements.get(c, c) for c in text)


# ============================================================
# CODE CLEANING
# ============================================================

def clean_code(code):
    code = code.replace("\r\n", "\n")
    code = code.replace("\r", "\n")

    # Remove trailing whitespace
    code = "\n".join(line.rstrip() for line in code.splitlines())

    # Don't allow huge empty gaps
    code = re.sub(r"\n{3,}", "\n\n", code)

    return code.strip()


# ============================================================
# METADATA
# ============================================================

def get_metadata(code, filepath):

    # Look only at the beginning of the file
    first_lines = "\n".join(code.splitlines()[:40])

    metadata = {}

    patterns = {
        "title": r"@title\s*:\s*(.+)",
        "complexity": r"@complexity\s*:\s*(.+)",
        "tags": r"@tags\s*:\s*(.+)",
        "priority": r"@priority\s*:\s*(\d+)",
    }

    for key, pattern in patterns.items():

        match = re.search(
            pattern,
            first_lines,
            re.IGNORECASE
        )

        if match:
            metadata[key] = match.group(1).strip()

    # If no title was specified, use filename
    if "title" not in metadata:

        title = filepath.stem

        title = title.replace("_", " ")
        title = title.replace("-", " ")

        metadata["title"] = title.title()

    if "complexity" not in metadata:
        metadata["complexity"] = ""

    if "tags" not in metadata:
        metadata["tags"] = ""

    if "priority" not in metadata:
        metadata["priority"] = "100"

    return metadata


# ============================================================
# CATEGORY
# ============================================================

def get_category(filepath):

    relative = filepath.relative_to(CODE_DIR)

    if len(relative.parts) == 1:
        return "misc"

    return relative.parts[0]


def category_name(category):

    if category in CATEGORIES:
        return CATEGORIES[category]

    return category.replace("_", " ").title()


# ============================================================
# FIND ALL CODES
# ============================================================

def find_codes():

    files = list(CODE_DIR.rglob("*.cpp"))

    def sort_key(filepath):

        category = get_category(filepath)

        if category in CATEGORIES:

            category_order = list(CATEGORIES.keys()).index(category)

        else:

            category_order = 999

        code = filepath.read_text(
            encoding="utf-8",
            errors="replace"
        )

        metadata = get_metadata(code, filepath)

        try:
            priority = int(metadata["priority"])
        except:
            priority = 100

        return (
            category_order,
            priority,
            metadata["title"].lower()
        )

    files.sort(key=sort_key)

    return files


# ============================================================
# REMOVE OUR METADATA COMMENT
# ============================================================

def remove_metadata(code):

    # Remove block containing @title, @complexity, etc.
    code = re.sub(
        r"/\*.*?@title.*?@priority.*?\*/",
        "",
        code,
        flags=re.DOTALL | re.IGNORECASE
    )

    return code.strip()


# ============================================================
# LATEX CODE BLOCK
# ============================================================

def latex_code(code):

    return (
        "\\begin{lstlisting}\n"
        + code
        + "\n"
        + "\\end{lstlisting}"
    )


# ============================================================
# BUILD LATEX DOCUMENT
# ============================================================

def build_latex(files):

    groups = {}

    for filepath in files:

        category = get_category(filepath)

        if category not in groups:
            groups[category] = []

        groups[category].append(filepath)

    latex = []

    # --------------------------------------------------------
    # DOCUMENT
    # --------------------------------------------------------

    latex.append(
        "\\documentclass[8pt,a4paper,landscape]{article}"
    )

    latex.append("\\usepackage[utf8]{inputenc}")
    latex.append("\\usepackage[T1]{fontenc}")
    latex.append("\\usepackage{lmodern}")

    latex.append(
        f"\\usepackage["
        f"margin={MARGIN},"
        f"top={MARGIN},"
        f"bottom={MARGIN}"
        f"]{{geometry}}"
    )

    latex.append("\\usepackage{multicol}")
    latex.append("\\usepackage{listings}")
    latex.append("\\usepackage{xcolor}")
    latex.append("\\usepackage{fancyhdr}")
    latex.append("\\usepackage{titlesec}")
    latex.append("\\usepackage{hyperref}")

    # --------------------------------------------------------
    # GENERAL SETTINGS
    # --------------------------------------------------------

    latex.append(
        "\\setlength{\\columnsep}{0.38cm}"
    )

    latex.append(
        "\\setlength{\\parindent}{0pt}"
    )

    latex.append(
        "\\setlength{\\parskip}{0pt}"
    )

    latex.append(
        "\\setlength{\\multicolsep}{2pt}"
    )

    # --------------------------------------------------------
    # CODE STYLE
    # --------------------------------------------------------

    latex.append("\\lstdefinestyle{cpp}{")

    latex.append(
        f"basicstyle=\\ttfamily\\fontsize"
        f"{{{FONT_SIZE}}}{{{LINE_HEIGHT}}}\\selectfont,"
    )

    latex.append("language=C++,")
    latex.append("columns=fullflexible,")
    latex.append("keepspaces=true,")
    latex.append("showstringspaces=false,")
    latex.append("breaklines=true,")
    latex.append("breakatwhitespace=false,")
    latex.append("tabsize=2,")
    latex.append("frame=none,")
    latex.append("aboveskip=1pt,")
    latex.append("belowskip=1pt,")
    latex.append("lineskip=-0.2pt")

    latex.append("}")

    latex.append("\\lstset{style=cpp}")

    # --------------------------------------------------------
    # HEADINGS
    # --------------------------------------------------------

    latex.append(
        "\\titleformat{\\section}"
        "{\\bfseries\\large}{}{0pt}{}"
    )

    latex.append(
        "\\titlespacing*{\\section}"
        "{0pt}{2pt}{1pt}"
    )

    # --------------------------------------------------------
    # HEADER
    # --------------------------------------------------------

    latex.append("\\pagestyle{fancy}")

    latex.append("\\fancyhf{}")

    latex.append(
        "\\fancyhead[C]"
        "{\\small\\bfseries LOS MAQUINOLAS --- ICPC TEAM BOOK}"
    )

    latex.append(
        "\\fancyfoot[C]{\\thepage}"
    )

    latex.append(
        "\\renewcommand{\\headrulewidth}{0.2pt}"
    )

    latex.append(
        "\\setlength{\\headheight}{10pt}"
    )

    latex.append(
        "\\hypersetup{colorlinks=false,pdfborder={0 0 0}}"
    )

    # --------------------------------------------------------
    # BEGIN DOCUMENT
    # --------------------------------------------------------

    latex.append("\\begin{document}")

    latex.append("\\begin{center}")

    latex.append(
        "{\\Large\\bfseries ICPC TEAM BOOK}\\\\[-1pt]"
    )

    latex.append(
        "{\\small Los Maquinolas --- Universidad Mayor de San Andrés}"
    )

    latex.append("\\end{center}")

    latex.append("\\vspace{-3pt}")

    latex.append(
        f"\\begin{{multicols}}{{{COLUMNS}}}"
    )

    # --------------------------------------------------------
    # CATEGORIES
    # --------------------------------------------------------

    ordered_categories = list(CATEGORIES.keys())

    # Add known categories first
    categories = []

    for category in ordered_categories:

        if category in groups:
            categories.append(category)

    # Then any unknown category
    for category in groups:

        if category not in categories:
            categories.append(category)

    for category in categories:

        title = category_name(category)

        latex.append(
            f"\\section*{{{latex_escape(title)}}}"
        )

        for filepath in groups[category]:

            raw_code = filepath.read_text(
                encoding="utf-8",
                errors="replace"
            )

            metadata = get_metadata(
                raw_code,
                filepath
            )

            code = clean_code(raw_code)

            code = remove_metadata(code)

            title = latex_escape(
                metadata["title"]
            )

            complexity = latex_escape(
                metadata["complexity"]
            )

            tags = latex_escape(
                metadata["tags"]
            )

            # ------------------------------------------------
            # ALGORITHM TITLE
            # ------------------------------------------------

            if complexity:

                latex.append(
                    f"\\textbf{{{title}}}"
                    f"\\hfill"
                    f"{{\\scriptsize {complexity}}}"
                    f"\\par"
                )

            else:

                latex.append(
                    f"\\textbf{{{title}}}\\par"
                )

            # ------------------------------------------------
            # TAGS
            # ------------------------------------------------

            if tags:

                latex.append(
                    f"{{\\scriptsize\\itshape {tags}}}\\par"
                )

            # ------------------------------------------------
            # CODE
            # ------------------------------------------------

            latex.append(
                latex_code(code)
            )

            latex.append(
                "\\vspace{1pt}"
            )

    # --------------------------------------------------------
    # END
    # --------------------------------------------------------

    latex.append("\\end{multicols}")

    latex.append("\\end{document}")

    return "\n".join(latex)


# ============================================================
# COMPILE LATEX
# ============================================================

def compile_latex():

    if shutil.which("pdflatex") is None:

        print()
        print("ERROR:")
        print("pdflatex was not found.")
        print()
        print(
            "Install MiKTeX or TeX Live first."
        )

        return False

    command = [
        "pdflatex",
        "-interaction=nonstopmode",
        "-halt-on-error",
        "-output-directory",
        str(OUTPUT_DIR),
        str(TEX_FILE)
    ]

    # Run twice for stable PDF generation
    for _ in range(2):

        result = subprocess.run(
            command,
            cwd=ROOT
        )

        if result.returncode != 0:
            return False

    return PDF_FILE.exists()


# ============================================================
# MAIN
# ============================================================

def main():

    CODE_DIR.mkdir(
        parents=True,
        exist_ok=True
    )

    OUTPUT_DIR.mkdir(
        parents=True,
        exist_ok=True
    )

    files = find_codes()

    if not files:

        print(
            "No .cpp files found!"
        )

        print()
        print(
            f"Put your codes inside: {CODE_DIR}"
        )

        sys.exit(1)

    print(
        f"Found {len(files)} C++ files."
    )

    tex = build_latex(files)

    TEX_FILE.write_text(
        tex,
        encoding="utf-8"
    )

    print(
        f"Generated {TEX_FILE}"
    )

    if compile_latex():

        print()
        print(
            f"SUCCESS!"
        )

        print(
            f"PDF: {PDF_FILE}"
        )

    else:

        print()
        print(
            "LaTeX compilation failed."
        )

        print(
            "The .tex file was generated, "
            "so you can inspect it."
        )

        sys.exit(1)


if __name__ == "__main__":
    main()