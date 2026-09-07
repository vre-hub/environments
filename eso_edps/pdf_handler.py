import os

from tornado.web import RequestHandler


class PdfHandler(RequestHandler):
    PDF_DIR = os.environ.get('EDPSGUI_PDF_DIR') or '.'

    def get(self):
        filename = os.path.join(self.PDF_DIR, self.get_argument('file'))
        self.set_header('Content-Type', 'application/pdf')
        with open(filename, 'rb') as f:
            self.write(f.read())


ROUTES = [('/pdf', PdfHandler, {})]
