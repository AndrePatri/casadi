# -*- coding: utf-8 -*-
#
# Configuration file for the Sphinx documentation builder.
#
# This file does only contain a selection of the most common options. For a
# full list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.

from typing import Any, Dict, List

# -- Project information -----------------------------------------------------

project = 'alpaqa'
copyright = '2021, Pieter Pas'
author = 'Pieter Pas'

# The short X.Y version
version = ''
# The full version, including alpha/beta/rc tags
release = ''

# -- General configuration ---------------------------------------------------

# If your documentation needs a minimal Sphinx version, state it here.
#
needs_sphinx = '4.0'

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autodoc',
    'sphinx.ext.coverage',
    'sphinx.ext.mathjax',
    'sphinx.ext.ifconfig',
    'sphinx.ext.viewcode',
    'sphinx.ext.githubpages',
    'sphinx.ext.doctest',
    'breathe',
    'matplotlib.sphinxext.plot_directive',
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['sphinxtemplates']

# The suffix(es) of source filenames.
# You can specify multiple suffix as a list of string:
#
# source_suffix = ['.rst', '.md']
source_suffix = '.rst'

# The master toctree document.
master_doc = 'index'

autodoc_default_options = {
    'members': None, # None means True here
    'undoc-members': None,
    'member-order': 'bysource',
    'class-doc-from': 'class',
    'special-members': '__init__, __call__',
}

# The language for content autogenerated by Sphinx. Refer to documentation
# for a list of supported languages.
#
# This is also used if you do content translation via gettext catalogs.
# Usually you set "language" from the command line for these cases.
language = 'en'

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns: List[str] = []

# The name of the Pygments (syntax highlighting) style to use.
pygments_style = 'default'

breathe_projects = {'alpaqa': "../../../build/xml"}
breathe_default_project = "alpaqa"

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
html_theme = 'furo'

html_logo = "../../logo/alpaqa_logo.svg"
html_favicon = "../../logo/alpaqa_favicon.png"

# Theme options are theme-specific and customize the look and feel of a theme
# further.  For a list of options available for each theme, see the
# documentation.
#
# html_theme_options = {}

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".
html_static_path = ['sphinxstatic']

html_css_files = [
    'css/custom.css',
]

# Custom sidebar templates, must be a dictionary that maps document names
# to template names.
#
# The default sidebars (for documents that don't match any pattern) are
# defined by theme itself.  Builtin themes are using these templates by
# default: ``['localtoc.html', 'relations.html', 'sourcelink.html',
# 'searchbox.html']``.
#
# html_sidebars = {}

# -- Options for HTMLHelp output ---------------------------------------------

# Output file base name for HTML help builder.
htmlhelp_basename = 'alpaqadoc'

# -- Options for LaTeX output ------------------------------------------------

latex_elements: Dict[str, Any] = {
    # The paper size ('letterpaper' or 'a4paper').
    #
    # 'papersize': 'letterpaper',

    # The font size ('10pt', '11pt' or '12pt').
    #
    # 'pointsize': '10pt',

    # Additional stuff for the LaTeX preamble.
    #
    # 'preamble': '',

    # Latex figure (float) alignment
    #
    # 'figure_align': 'htbp',
}

# Grouping the document tree into LaTeX files. List of tuples
# (source start file, target name, title,
#  author, documentclass [howto, manual, or own class]).
title_string = 'alpaqa documentation'

latex_documents = [
    (master_doc, 'alpaqa.tex', title_string, 'Pieter Pas', 'manual'),
]

# -- Options for manual page output ------------------------------------------

# One entry per manual page. List of tuples
# (source start file, name, description, authors, manual section).
man_pages = [(master_doc, 'alpaqa', title_string, [author], 1)]

# -- Options for Texinfo output ----------------------------------------------

# Grouping the document tree into Texinfo files. List of tuples
# (source start file, target name, title, author,
#  dir menu entry, description, category)
texinfo_documents = [
    (master_doc, 'alpaqa', title_string, author, 'alpaqa',
     'One line description of project.', 'Miscellaneous'),
]

# -- Options for Epub output -------------------------------------------------

# Bibliographic Dublin Core info.
epub_title = project

# The unique identifier of the text. This can be a ISBN number
# or the project homepage.
#
# epub_identifier = ''

# A unique identification for the text.
#
# epub_uid = ''

# A list of files that should not be packed into the epub file.
epub_exclude_files = ['search.html']

# -- Extension configuration -------------------------------------------------

plot_formats = ['svg']

# -- Add MathJax macros ------------------------------------------------------

# For now, these are added manually. They are generated by Doxygen from the
# doxygen/macros.tex file.

mathjax3_config = {
    'tex': {
        'macros': {
        'Reals': "{\\mathrm{I\\!R}}",
        'Nats': "{\\mathrm{I\\!N}}",
        'Cplx': "{\\mathbb{C}}",
        'R': "{\\Reals}",
        'N': "{\\Nats}",
        'C': "{\\Cplx}",
        'Rn': "{\\Reals^n}",
        'gph': "{\\operatorname{\\mathbf{gph}}}",
        'zer': "{\\operatorname{\\mathbf{zer}}}",
        'fix': "{\\operatorname{\\mathbf{fix}}}",
        'prox': "{\\operatorname{\\mathbf{prox}}}",
        'Hilb': "{\\mathcal{H}}",
        'proj': ["{\\operatorname{\\mathbf{\\Pi}_\\mathnormal{#1}}}",1],
        'Id': "{\\mathrm{Id}}",
        'one': "{\\mathbf{1}}",
        'defeq': "{\\triangleq}",
        'minimize': "{\\operatorname*{\\mathbf{minimize}}}",
        'maximize': "{\\operatorname*{\\mathbf{maximize}}}",
        'argmin': "{\\operatorname*{\\mathbf{arg\\,min}}}",
        'argmax': "{\\operatorname*{\\mathbf{arg\\,max}}}",
        'inprod': ["{\\left\\langle {#1} \\,\\middle|\\, {#2} \\right\\rangle}",2],
        'norm': ["{\\left\\| {#1} \\vphantom{X} \\right\\|}",1],
        'normsq': ["{\\norm{#1}^2}",1],
        'defset': ["{\\left\\{ {#1} \\middle| {#2} \\right\\}}",2],
        'tp': ["{#1^\\top}",1],
        'herm': ["{#1^\\mathrm{H}}",1],
        'invherm': ["{#1^{-\\mathrm{H}}}",1],
        'inv': ["{#1^{-1}}",1],
        'pinv': ["{#1^\\dagger}",1],
        'conj': "{\\overline}",
        'sconj': ["{#1^*}",1],
        'iddots': "{\\mathinner{\\kern1mu\\raise1pt{.}\\kern2mu\\raise4pt{.}\\kern2mu\\raise7pt{\\Rule{0pt}{7pt}{0pt}.}\\kern1mu}}",
        'imagfun': ["{\\left(#1\\right)\\left(#2\\right)}",2],
        'Lagr': "{\\mathcal{L}}",
        'dft': "{\\operatorname{\\mathbf{dft}}}",
        'cbrt': ["{\\sqrt[3]{#1}}",1],
        'sgn': "{\\operatorname{\\mathbf{sgn}}}",
        'setmap': "{\\rightrightarrows}",
        'lammin': "{\\lambda_\\text{min}}",
        'lammax': "{\\lambda_\\text{max}}",
        'Sc': "{\\mathcal{S}}",
        'Scstar': "{\\mathcal{S}^*}",
        'diag': "{\\operatorname{\\mathbf{diag}}}",
        'blkdiag': "{\\operatorname{\\mathbf{blkdiag}}}",
        'posdef': "{\\succ}",
        'possdef': "{\\succeq}",
        'half': "{\\tfrac{1}{2}}",
        },
        'packages': ['base','configmacros','newcommand','ams'],
        'tags': 'ams',
    },
    'loader': {'load': ['[tex]/newcommand']},
}